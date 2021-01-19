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

#define MAX_DB 2147483647.0

/*
**  Fun create_rgb
**  
**  Example:
** r -> 155  (10011011)
** g -> 240  (11110000)
** b -> 100  (01100100)
** (r << 16) -> (100110110000000000000000) (plus 16 zero bit)
** (g << 8) -> (1111000000000000)
** b ->   (01100100)
** "l" -> oretion OR (bits)
**    (100110110000000000000000)
** or (000000001111000000000000)
**    (000000000000000001100100)
** res(100110111111000001100100)
*/


typedef struct  s_pixel 
{
    double          t;
    t_rgb           rgb;
    t_xyz           cor;
    int             specular;
    double          reflective;

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
**  Create vect in 2 point 
**
**  b - a
**  return -> vector xyz
*/

 t_xyz   ft_reflect_ray(t_xyz r, t_xyz n) 
 {
    t_xyz res;

    res = ft_xyz_mult_db(n,2);
    res = ft_xyz_mult_db(res,ft_xyz_scal(n,r));
    res = ft_xyz_minus(res,r);

    return (res);
    //return 2*N*dot(N, R) - R;
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

double  ft_intersect_ray_sphere(t_xyz o, t_xyz d,t_pixel *pixel,t_sphere *spher,double t_min,double t_max)
{
    t_xyz oc;
    t_kf_abc abc;
    (void) pixel;
    t_xyz p1;

    oc = ft_xyz_minus(o,spher->coord_sph_centr);    
    abc.a = ft_xyz_scal(d,d);
    abc.b = 2 * ft_xyz_scal(oc,d);
    abc.c = ft_xyz_scal(oc,oc) - pow(spher->diametr ,2);
   
    if ((abc.discr = abc.b * abc.b - 4 * abc.a * abc.c ) < 0.0)
        return(MAX_DB);
    abc.t1 = (-abc.b + sqrt(abc.discr)) / (2*abc.a);
    abc.t2 = (-abc.b - sqrt(abc.discr)) / (2*abc.a);
    if ((abc.t1 < abc.t2) && (abc.t1 < pixel->t) && (abc.t1 > t_min)  && (abc.t1 < t_max))
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
        n = ft_xyz_div_db(n,ft_len_vect(n));
        pixel->cor = n;
    }
    else if ((abc.t2 <= abc.t1) && (abc.t2 < pixel->t) && (abc.t2 > t_min) && (abc.t2 < t_max))
    {
       // printf("!!!!\n");
        pixel->rgb = spher->rgb;
        pixel->t = abc.t2;
        
        pixel->specular = spher->specular;
        pixel->reflective = spher->reflective;
        p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
        t_xyz n;
        n = ft_xyz_minus(p1,spher->coord_sph_centr);
        n = ft_xyz_div_db(n,ft_len_vect(n));
        pixel->cor = n;
        //return (t2);
    } 
    return (0.0);  
}

void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,double t_min,double t_max, t_plane *pl)
{
    double t;
    double rn;
    double ln;
    t_xyz r;

    ln = ft_xyz_scal(pl->normal_orientr_vec,d);
    r = ft_xyz_minus(pl->cord, o);
    rn = ft_xyz_scal(pl->normal_orientr_vec,r) - pl->normal_orientr_vec.x * pl->cord.x -  pl->normal_orientr_vec.y * pl->cord.y -  pl->normal_orientr_vec.z * pl->cord.z;
    if (fabs(ln) <  0.0001)
        return;
    t = -rn / ln;
    if ((ln > 0 && rn > 0.0) || (ln < 0 && rn < 0.0))
        return;
    if ( t < pixel->t  && t > t_min && t <  t_max)
    {
        //printf("ku ku\n");
        pixel->t = t;
        pixel->rgb = pl->rgb;
        pixel->cor = pl->normal_orientr_vec;
        pixel->specular = 100;
        pixel->reflective = 0.3;
        //pixel->specular = spher->specular;
        //pixel->reflective = spher->reflective;
    }
}

double ClosestIntersection(t_all_obj *all_obj,t_xyz o, t_xyz v)
{
    //double t = MAX_DB;
    t_pixel pixel;

    pixel.t = MAX_DB;


    //t_xyz o;
    t_xyz d;
    t_xyz c;
    t_xyz oc;

    d = v; 

    t_list *sp;
    t_sphere *spher;

    sp = all_obj->l_sphere;

    //printf("Hello\n");
    while (sp)
    {
                spher = sp->content;
                c  =   spher->coord_sph_centr;
                oc = ft_xyz_minus(o,c);    
                ft_intersect_ray_sphere(o,d,&pixel,spher,0.0001,0.99);
                sp = sp->next;
    }

    t_list  *l_pl;
    t_plane *pl;
    l_pl = all_obj->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        //printf("%d 1 pl\n", pl->rgb.red);
        ft_intersect_pl(o,d,&pixel,0.001,MAX_DB,pl);
        if (pixel.t != MAX_DB)
            printf("DMFSND\n");
        l_pl = l_pl->next;
    }

    return (pixel.t);
}

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/



t_rgb  ft_compute_lighting_sp(t_all_obj *all_obj,t_xyz p, t_xyz n,t_xyz v,int s,t_rgb rgbmy)
{
    double i;
    double n_don_l;
    double r_dot_v;
    t_xyz l;
    t_list *light_all;
    t_light *li;
    t_xyz r;
    t_rgb	color_pix;
	color_pix = ft_rgb_mult_db(rgbmy,all_obj->al.light);//  rgbmy;//(t_rgb){0, 0, 0};   
    color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(all_obj->al.rgb,all_obj->al.light));
    i = all_obj->al.light;
    //printf("p  x:%f y:%f z: %f\n",p.x,p.y,p.z);
    //printf("n  x:%f y:%f z: %fs\n",n.x,n.y,n.z);
    light_all = all_obj->l_light;
    //color_pix = ft_rgb_mult_db(all_obj->al.rgb, 1.0);//all_obj->al.light);
    while(light_all)
    {
        li = light_all->content;
        l =  ft_xyz_minus(li->cord_l_point,p);
        if (li->rgb.red == 245)
        {
            l = li->cord_l_point;
        }

        n_don_l = ft_xyz_scal(n,l);

        //ClosestIntersection
        // проверяем доходит ли цвет
        /*if (ClosestIntersection(all_obj,p,l) != MAX_DB)
        {
            light_all = light_all->next;
            continue;
        }*/
        // просто цвет
        if (n_don_l > 0.0)
        {
            
            i =  li->light_brightness * n_don_l /( ft_len_vect(n) * ft_len_vect(l));
            color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
        }

        // отражения
        if (s > 0)
        {
            r = ft_xyz_mult_db(n,2.0);
            r = ft_xyz_mult_db(r,ft_xyz_scal(n,l));
            r = ft_xyz_minus(r,l);
            //r = ft_xyz_div_doub( ft_xyz_mult( 2*ft_xyz_mult_xyz(n,l));
            r_dot_v = ft_xyz_scal(r, v);
            if (r_dot_v > 0.0)
            {
                    i = li->light_brightness * pow(r_dot_v/(ft_len_vect(r) * ft_len_vect(v)), s);
                    color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
            }
        }

        light_all = light_all->next;
    }    
    return (color_pix);
}




/*
**  ft_ray_trace
**  
**  
**
**  return (rgb) color in pixel
*/


//цвет шара * кф общего освещения + общее освещение * кф


t_rgb     ft_ray_trace(t_all_obj *all_obj,t_xyz o,t_xyz d,double t_min,double t_max,int rec)
{
    t_list *sp;
    t_sphere *spher;
    t_xyz p;
    t_xyz n;

    t_pixel pixel;
    pixel.t = MAX_DB;
    pixel.rgb = ft_rgb_mult_db(all_obj->al.rgb,all_obj->al.light);

    sp = all_obj->l_sphere;
    while (sp)
    {
            spher = sp->content;
            ft_intersect_ray_sphere(o,d,&pixel,spher,t_min,t_max);
            sp = sp->next;
    }


    t_list  *l_pl;
    t_plane *pl;
    l_pl = all_obj->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        //printf("%d 1 pl\n", pl->rgb.red);
        ft_intersect_pl(o, d, &pixel,t_min,t_max,pl);
        l_pl = l_pl->next;
    }


    if (pixel.t == MAX_DB)
        return (pixel.rgb);

    p = ft_xyz_plus(o , ft_xyz_mult_db(d,pixel.t));
    //n = ft_xyz_minus(p,pixel.cor);
    //n = ft_xyz_div_db(n,ft_len_vect(n));
    n = pixel.cor;
    pixel.rgb = ft_compute_lighting_sp(all_obj,p,n,ft_xyz_mult_db(d,-1.0),pixel.specular,pixel.rgb);
   
    if (rec <=  20000 || pixel.reflective <= 2220.001)
        return(pixel.rgb);
    t_xyz r;
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),n);
    t_pixel pixel2;
    pixel2.t = MAX_DB;
    pixel2.rgb = all_obj->al.rgb;
    t_rgb ref_color;
    ref_color = ft_ray_trace(all_obj,p,r,0.001,MAX_DB,rec - 1);
    t_rgb new;
    new = ft_rgb_mult_db(pixel.rgb,1.0 - pixel.reflective);
    new = ft_rgb_plus_rgb(new, ft_rgb_mult_db(ref_color,pixel.reflective));
    return(new);
    
}

t_xyz   ft_create_vec_d(t_all_obj *all_obj, double x, double y)
{
    t_xyz c_r;
    t_xyz c_up;
    t_xyz d;
    t_xyz v;
    double fov;
    
    fov  =  2 * tan(all_obj->camera.FOV / 2 * 3.14 / 180);
    x *= fov;
    y *= fov;
    v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1);
    c_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0},all_obj->camera.camera_direction);
    c_up = ft_xyz_mult_xyz(all_obj->camera.camera_direction,c_r);
    d = ft_r_u_n_mult_xyz(c_r,c_up,all_obj->camera.camera_direction,v);
    return (d);
}

int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    clock_t begin = clock();
    int cx;
    int cy;
    double x;
    double y;
    t_rgb rgb;
    t_xyz d;
    
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
            //d = ft_xyz_normalaze(d);
            rgb = ft_ray_trace(all_obj, all_obj->camera.coord_pointer, d , 0.0 ,MAX_DB,5);
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
