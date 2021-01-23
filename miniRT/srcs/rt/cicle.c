/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/15 11:16:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include "mlx.h"
#include <rgb.h>
#include <pthread.h>

#define MAX_DB 2147483648.0

typedef struct  s_range 
{
    double      min;
    double      max;
}               t_range;


typedef struct  s_pixel 
{
    double          t;
    t_rgb           rgb;
    t_xyz           normal;
    int             specular;
    double          reflective;
    int             id;
}                t_pixel;

typedef struct  s_kf_abc 
{
    double          a;
    double          b;
    double          c;
    double          t1;
    double         t2;
    double         discr;
}                t_kf_abc;

int     ft_in_range(t_range range, double a)
{
    if (a >= range.min && a <= range.max)
        return (1);
    return (0);    
} 

/*
** cx and cy -> coordinat pixel in window system
*/

/*
**  Converter x Screen coordinat to decart coordinat
**
**  cx -> coordinat x for Scr
**  width -> width window
**  xmin  -> minimal x in decart system
**  xmax  -> maximal x in decart system
**  return -> x for decart system
*/

double  ft_convert_scr_to_dec_x(int cx, int width, double xmin, double xmax)
{
    double x;
    double xsize;
    double w;

    w = width;
    xsize = xmax - xmin;
    x = xmin + (cx / w) * xsize;
    return (x);
    //return ((double)cx - (double)width / 2);
}

/*
**  Converter y Screen coordinat to decart coordinat
**
**  cy -> coordinat y for Scr
**  width -> width window
**  ymin  -> minimal y in decart system
**  ymax  -> maximal y in decart system
**  return -> y for decart system
*/

double  ft_convert_scr_to_dec_y(int cy, int height, double  ymin, double  ymax)
{
    double y;
    double ysize;
    double h;
    
    h = height;
    ysize = ymax - ymin;
    y = ymax - (cy / h) * ysize;
    return (y);
}

/*
**  Create viewport vector
**
**  x -> coordinat 
**  y -> coordinat
**  width window
**  height window
**  Vx = Cx * Vw/Cw
**  Vy = Cy * Vh/Ch
**  Vz = d
**  z -> z
**  return -> vector xyz
*/

t_xyz      ft_create_v(double x, double y, int width, int height, double z)
{
    t_xyz v;

    (void) width;
    (void)  height;
    (void) z;

    v.x =   x  / height;//- (width/2);
    v.y =   y * (1.0/height); //(height/2)-y;
    v.z =   z;
    return (v);
}

/*
**  Reflected relative to n ray
**  r - vec
**  n - normal
**  /return 2 * N * dot(N, R) - R;
*/

 t_xyz   ft_reflect_ray(t_xyz r, t_xyz n) 
 {
    t_xyz res;

    res = ft_xyz_mult_db(n,2);
    res = ft_xyz_mult_db(res,ft_xyz_scal(n,r));
    res = ft_xyz_minus(res,r);
    return (res);
}

/*  
**   ft_recurse_color
**
**   return local_color * (1 - r) + reflected_color * r
*/

t_rgb   ft_recurse_color(t_rgb  ref_col, t_rgb  loc_col, double reflective)
{
    t_rgb res;

    res = ft_rgb_mult_db(loc_col,1 - reflective);
    res = ft_rgb_plus_rgb(res, ft_rgb_mult_db(ref_col,reflective));
    return (res);
}
/*
**  the quadratic equation 
**  D = B^2 - 4 * A * C 
**  
**  return -> MINIMAL X OR INFINITY
*/


/*
**  Sphere:
** P - point lutch
** C - Center sphere
** 
** |P - C| = r
** 
**  <P - C, P - C > = r ^ 2
**
** D = V - O
**
** and  P = O + t * D
** 
*/

double  ft_intersect_ray_sphere(t_xyz o, t_xyz d,t_pixel *pixel,t_sphere *spher,t_range range)
{
    t_xyz oc;
    t_kf_abc abc;
    t_xyz p1;

    oc = ft_xyz_minus(o,spher->coord_sph_centr);    
    abc.a = ft_xyz_scal(d,d);
    abc.b = 2 * ft_xyz_scal(oc,d);
    abc.c = ft_xyz_scal(oc,oc) - pow(spher->diametr ,2);
    if ((abc.discr = abc.b * abc.b - 4 * abc.a * abc.c ) < 0.0)
        return(MAX_DB);
    abc.t1 = (-abc.b + sqrt(abc.discr)) / (2*abc.a);
    abc.t2 = (-abc.b - sqrt(abc.discr)) / (2*abc.a);
   
    if((abc.t1 >= 0.0 && abc.t2 <= 0.0) || (abc.t2 >= 0.0 && abc.t1 <= 0.0)) 
    {
        if ( (abc.t1) < pixel->t  && ft_in_range(range,abc.t1))
        {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            //pixel->cor = spher->coord_sph_centr;
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t * 0.9999));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal = ft_xyz_div_db(n,ft_len_vect(n));
            return (0.0);


        }
        else if ((abc.t2 < pixel->t) && ft_in_range(range,abc.t2))
        {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t2;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t * 0.9999));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal = ft_xyz_div_db(n,ft_len_vect(n));
            return (0.0);

        }
        return (0.0);
    }
    else if ((abc.t1 < abc.t2) && (abc.t1 < pixel->t) && ft_in_range(range,abc.t1))
    {
    
            //printf("!!!!\n");
            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            //pixel->cor = spher->coord_sph_centr;
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal =ft_xyz_div_db(n,ft_len_vect(n));
    }
    else if ((abc.t2 <= abc.t1) && (abc.t2 < pixel->t) && ft_in_range(range,abc.t2))
    {
       // printf("!!!!\n");

        if (ft_len_vect(oc) < spher->diametr) 
        {

            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal = ft_xyz_div_db(n,ft_len_vect(n));    
        
        }
        else {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t2;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal = ft_xyz_div_db(n,ft_len_vect(n));
        }
        //return (t2);
    } 
    return (0.0);  
}

void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range range, t_plane *pl)
{
    double t;
    double dn;
    double on;
    double dd;

    //pl->normal_orientr_vec = ft_xyz_mult_db(pl->normal_orientr_vec,1.0);
    
    dd = -ft_xyz_scal(pl->normal_orientr_vec, pl->cord);
    dn = ft_xyz_scal(pl->normal_orientr_vec,d);
    on = ft_xyz_scal(pl->normal_orientr_vec,o) + dd;
    if (dn == 0)
        return;
    if (fabs(dn) <  0.0000001)
        return;  
    //printf("ku ku\n");
    t = -on / dn;
    if (t < pixel->t  && ft_in_range(range,t))
    {
        //printf("ku ku\n");
        //if (ft_xyz_scal() )
        pixel->t = t;
        pixel->rgb = pl->rgb;
        pixel->normal = pl->normal_orientr_vec;
        pixel->specular = 0;//400;
        pixel->reflective = 0;
        pixel->id = plane;
    }
}

void    ft_intersect_ray_triangle(t_xyz o,t_xyz d,t_pixel *pixel,t_triangle *tr,t_range range)
{

    /*printf("1: %f \n",tr->first_point.x);
    printf("2: %f \n",tr->first_point.y);
    printf("3: %f \n",tr->first_point.z);

    printf("\n1: %f \n",tr->second_point.x);
    printf("2: %f \n",tr->second_point.y);
    printf("3: %f \n",tr->second_point.z);

        printf("\n1: %f \n",tr->third_point.x);
    printf("2: %f \n",tr->third_point.y);
    printf("3: %f \n",tr->third_point.z);*/

    t_xyz v1;
    t_xyz v2;
    t_xyz n;
    t_xyz v1d;
    double scal_v2_v1d;
    double t;

    v1 = ft_xyz_minus(tr->second_point,tr->first_point);
    v2 = ft_xyz_minus(tr->third_point,tr->first_point);
    n = ft_xyz_mult_xyz(v1,v2);
    v1d = ft_xyz_mult_xyz(v2,d);
    scal_v2_v1d = ft_xyz_scal(v1,v1d);
    if (fabs(scal_v2_v1d) < 0.01)
        return;
     t_xyz vec;

    vec = ft_xyz_minus(o, tr->first_point);
    double u;
    u = ft_xyz_scal(vec,v1d) / scal_v2_v1d;   
    if (u < 0.0 || u > 1.0)
        return ;
    t_xyz q_vec;
    q_vec = ft_xyz_mult_xyz(v1,vec); 
    double v;
    v = ft_xyz_scal(d,q_vec) / scal_v2_v1d;
    if (v < 0.0 || u + v > 1.0)
        return ;
    t = ft_xyz_scal(v2, q_vec) / scal_v2_v1d;
    if (t < pixel->t  && ft_in_range(range,t))
    {

        //printf("ku ku\n");
        //if (ft_xyz_scal() )
        pixel->t = t;
        pixel->rgb = tr->rgb;
        
        pixel->normal = n;
        pixel->specular = 0;//400;
        pixel->reflective = 0;
        pixel->id = triangle;
    }
}



/*
**  o vec -> point in obk=ject
**  d -> vec in light
**
**
*/

double ClosestIntersection(t_all_obj *all_obj,t_xyz o, t_xyz d)
{
    t_pixel pixel;
    
    pixel.t = MAX_DB;

    t_xyz c;
    t_xyz oc;
    t_list *sp;
    t_sphere *spher;

    sp = all_obj->l_sphere;

    while (sp)
    {
        spher = sp->content;
        c  =   spher->coord_sph_centr;
        oc = ft_xyz_minus(o,c);    
        ft_intersect_ray_sphere(o,d,&pixel,spher,(t_range){0.0001,0.9999});
        sp = sp->next;
    }

    t_list  *l_pl;
    t_plane *pl;
    l_pl = all_obj->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        //pl->normal_orientr_vec = ft_xyz_mult_db(pl->normal_orientr_vec,-1.0);
        ft_intersect_pl(o,d,&pixel,(t_range){0.000000000000001,0.99999},pl);
        l_pl = l_pl->next;
    }

    t_list *l_tr;
    t_triangle *tr;
    l_tr = all_obj->l_tr;
    while (l_tr)
    {
        tr = l_tr->content;
        ft_intersect_ray_triangle(o,d,&pixel,tr, (t_range){0.0000001,0.99999});
        l_tr = l_tr->next;
    }

    return (pixel.t);
}

/*
**   ft_compute_lighting_sp
**  all_object
**  point (p) in object
**  n -> normal vec
**  v -> vec in (-d)
*/


t_rgb  ft_compute_lighting_sp(t_all_obj *all_obj,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
{
    (void) v;
    double i;
    double n_don_l;
    double r_dot_v;
    t_xyz l;
    t_list *l_light;
    t_light *li;
    t_xyz r;
    t_rgb	color_pix;
	color_pix = ft_rgb_mult_db(pixel->rgb,all_obj->al.light);//  rgbmy;//(t_rgb){0, 0, 0};   
    color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(all_obj->al.rgb,all_obj->al.light));
    i = all_obj->al.light;
    l_light = all_obj->l_light;
    while(l_light)
    {
        li = l_light->content;
        l =  ft_xyz_minus(li->cord_l_point,p);
        n_don_l = ft_xyz_scal(n,l);
        
        if (n_don_l <= 0.0 && (pixel->id == plane || pixel->id == triangle))
        {
            n = ft_xyz_mult_db(n,-1.0);
            n_don_l = ft_xyz_scal(n,l);
        }

        //ClosestIntersection
        // проверяем доходит ли цвет
        if (ClosestIntersection(all_obj, p , l) != MAX_DB)
        {
            l_light = l_light->next;
            continue;
        }

        // просто цвет
        if (n_don_l >= 0.0 )
        {
            i =  li->light_brightness * n_don_l /( ft_len_vect(n) * ft_len_vect(l));
            color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
        }

        if (pixel->specular > 0 && n_don_l >= 0.0)
        {
            r = ft_reflect_ray(n,l);
            r_dot_v = ft_xyz_scal(r, v);
            if (r_dot_v > 0.0)
            {   
                    i = li->light_brightness * pow(r_dot_v/(ft_len_vect(r) * ft_len_vect(v)), pixel->specular);
                    color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
            }
        }

        l_light = l_light->next;
    }    
    return (color_pix);
}




/*
**  ft_l_pl
** all_obj -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/

void        ft_l_pl(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d)
{
    t_list  *l_pl;
    t_plane *pl;

    l_pl = all_obj->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        ft_intersect_pl(o, d, pixel,(t_range){0.0000001,MAX_DB},pl);
        l_pl = l_pl->next;
    }
}

/*
**  ft_l_sphere
**  all_obj -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/

void       ft_l_sphere(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d)
{
    t_list      *l_sp;
    t_sphere    *spher;

    l_sp = all_obj->l_sphere;
    while (l_sp)
    {
        spher = l_sp->content;
        ft_intersect_ray_sphere(o,d,pixel,spher, (t_range){0.0000001,MAX_DB});
        l_sp = l_sp->next;
    }
}



void    ft_l_tr(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d)
{
    t_list      *l_tr;
    t_triangle  *tr;

    l_tr = all_obj->l_tr;
    while (l_tr)
    {
        tr = l_tr->content;
        ft_intersect_ray_triangle(o,d,pixel,tr, (t_range){0.0000001,MAX_DB});
        l_tr = l_tr->next;
    }

}

/*
**  ft_ray_trace
**  all_obj -> struct in rt
**  vec o -> point start in lutch (camera)
**  vec d -> lutch in ray_trace
**  range -> min and max kf for d 
**  p = o + D * t 
**  return (rgb) color in pixel
*/

t_rgb     ft_ray_trace(t_all_obj *all_obj,t_xyz o,t_xyz d,t_range range,int rec)
{
    t_xyz   p;
    t_xyz   r;
    t_pixel pixel;
    t_rgb   ref_color;
    
    pixel.t = MAX_DB;
    pixel.rgb = ft_rgb_mult_db(all_obj->al.rgb,all_obj->al.light);
    ft_l_sphere(all_obj, &pixel, o, d);
    ft_l_pl(all_obj, &pixel, o, d);
    ft_l_tr(all_obj,&pixel,o, d);
    if (pixel.t == MAX_DB)
        return (pixel.rgb);
    p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel.t * 0.999999));
    pixel.rgb = ft_compute_lighting_sp(all_obj,  p, pixel.normal,ft_xyz_mult_db(d, -1.0),&pixel);
    if (rec <=  0 || pixel.reflective <= 0.000001)
        return(pixel.rgb);
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel.normal);
    ref_color = ft_ray_trace(all_obj, p, r,range,rec - 1);
    return(ft_recurse_color(ref_color, pixel.rgb, pixel.reflective));
}

t_xyz   ft_create_vec_d(t_all_obj *all_obj, double x, double y)
{
    t_xyz   c_r;
    t_xyz   c_up;
    t_xyz   d;
    t_xyz   v;
    double  kf;
    
    kf  =  2 * tan(all_obj->camera.FOV / 2 * 3.14 / 180);
    x *= kf;
    y *= kf;
    v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1);
    c_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0},all_obj->camera.camera_direction);
    c_up = ft_xyz_mult_xyz(all_obj->camera.camera_direction,c_r);
    d = ft_r_u_n_mult_xyz(c_r,c_up,all_obj->camera.camera_direction,v);
    return (d);
}

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/

int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    clock_t begin = clock();
    int cx;
    int cy;
    double x;
    double y;
    t_rgb rgb;
    t_xyz d;
    printf("true %d \n",TRUE);
    all_obj->camera.camera_direction = ft_xyz_normalaze(all_obj->camera.camera_direction);
    cx = 0;
    cy = 0;
    while (cy < all_obj->reso.height)
    {
        while(cx < all_obj->reso.width)
        {    
            x =  ft_convert_scr_to_dec_x(cx, all_obj->reso.width, -(all_obj->reso.width / 2), all_obj->reso.width / 2);
            y =  ft_convert_scr_to_dec_y(cy, all_obj->reso.height, -(all_obj->reso.height / 2), all_obj->reso.height / 2); 
            d =  ft_create_vec_d(all_obj , x ,y);
            rgb = ft_ray_trace(all_obj, all_obj->camera.coord_pointer, d ,(t_range){0.0001,MAX_DB},5);
            mlx_pixel_put(vars->mlx,vars->win,cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            cx++;
        }
        cx = 0;
        cy++;
    }  
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TIME %f sec\n",time_spent);
    return (1);
}
