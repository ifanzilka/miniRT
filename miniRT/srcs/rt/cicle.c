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

#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include "mlx.h"

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

int		create_rgb( int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

/*
** 0xFF -> all bits (1)
*/



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

    v.x =  x * (1.0/width) * width / height;//- (width/2);
    v.y = y * (1.0/height);//(height/2)-y;
    v.z =  1;
    return (v);
}

t_xyz      ft_create_v2(double x, double y, int width, int height, double z)
{
    t_xyz v;

    (void) width;
    (void)  height;
    (void) z;
    v.x =  x / width;
    v.y =  y / height;
    v.z =  z;
    return (v);
}

/*
**  Create  vector xyz
**
**  x -> coordinat 
**  y -> coordinat
**  z -> coordinat
**  return -> vector xyz
*/

t_xyz      ft_create_xyz(double x, double y,double z)
{
    t_xyz o;

    o.x = x;
    o.y = y;
    o.z = z;
    return (o);
}

/*
**  Operation minus  vector xyz
**
**   a - b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_minus(t_xyz a, t_xyz b)
{
    t_xyz res;

    
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

/*
**  Operation plus  vector xyz
**
**   a + b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_plus(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return (res);
}

/*
**  Operation mult  vector xyz
**
**   a * b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_mult(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    return (res);
} 


/*
**  Operation div  vector xyz
**
**   a / b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_div_doub(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    return (res);
}

/*
** Len  vector xyz
**
**  return -> Len xyz
*/

double ft_len_vect(t_xyz a)
{
    double len;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (len);
}

/*
**  Operation scalar mult  vector xyz 
**
**   <a , b >
**  return -> vector xyz
*/

double ft_xyz_mult_xyz(t_xyz a, t_xyz b)
{
    double res;

    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return (res);
}

/*
**  Create vect in 2 point 
**
**  b - a
**  return -> vector xyz
*/

t_xyz   ft_vect_two_point(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = b.x - a.x;
    res.y = b.y - a.y;
    res.z = b.z - a.z;
    return (res);
}
int     ft_max3(int a, int b,int c)
{
    int max;
    max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    return (max);        
}
t_rgb   ft_rgb_mult_db(t_rgb rgb, double a)
{
    int max;
    rgb.red = (int)((double)rgb.red * a);
    rgb.green = (int)((double)rgb.green * a);
    rgb.blue = (int)((double)rgb.blue * a);

    max = ft_max3(rgb.red,rgb.green,rgb.blue);
    /*if (max > 255)
    {
        rgb.red = (255 / max )* rgb.red;
        rgb.green = (255 / max )* rgb.green;
        rgb.blue = (255 / max )* rgb.blue;
    }*/

    if (rgb.red > 255)
        rgb.red = 255;
    if (rgb.green > 255)
        rgb.green = 255;
    if (rgb.blue > 255)
        rgb.blue = 255;
    return (rgb);           
}



t_rgb   ft_rgb_plus_rgb(t_rgb a, t_rgb b)
{
    t_rgb rgb;
    int max;
    rgb.red = a.red + b.red;
    rgb.green = a.green + b.green;
    rgb.blue = a.blue + b.blue;
    max = ft_max3(rgb.red,rgb.green,rgb.blue);
    if (max > 255)
    {
        rgb.red = (255 / max )* rgb.red;
        rgb.green = (255 / max )* rgb.green;
        rgb.blue = (255 / max )* rgb.blue;
    }
    /*if (rgb.red > 255)
        rgb.red = 255;
    if (rgb.green > 255)
        rgb.green = 255;
    if (rgb.blue > 255)
        rgb.blue = 255;*/
    return (rgb); 
}



 t_xyz   ft_reflect_ray(t_xyz r, t_xyz n) 
 {
    t_xyz res;

    res = ft_xyz_mult(n,2);
    res = ft_xyz_mult(res,ft_xyz_mult_xyz(n,r));
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


double  ft_intersect_ray_sphere(t_xyz o, t_xyz d,t_pixel *pixel,t_sphere *spher,double t_min,double t_max)
{
    t_xyz oc;
    t_kf_abc abc;
    (void) pixel;

    oc = ft_xyz_minus(o,spher->coord_sph_centr);    
    abc.a = ft_xyz_mult_xyz(d,d);
    abc.b = 2 * ft_xyz_mult_xyz(oc,d);
    abc.c = ft_xyz_mult_xyz(oc,oc) - pow(spher->diametr ,2);
    if ((abc.discr = abc.b * abc.b - 4 * abc.a * abc.c ) < 0.0)
        return(MAX_DB);
    abc.t1 = (-abc.b + sqrt(abc.discr)) / (2*abc.a);
    abc.t2 = (-abc.b - sqrt(abc.discr)) / (2*abc.a);
    if ((abc.t1 < abc.t2) && (abc.t1 < pixel->t) && (abc.t1 > t_min)  && (abc.t1 < t_max))
    {
        //printf("!!!!\n");
        pixel->rgb = spher->rgb;
        pixel->t = abc.t1;
        pixel->cor = spher->coord_sph_centr;
        pixel->specular = spher->specular;
        pixel->reflective = spher->reflective;
                //return (t1);
    }
    else if ((abc.t2 <= abc.t1) && (abc.t2 < pixel->t) && (abc.t2 > t_min) && (abc.t2 < t_max))
    {
       // printf("!!!!\n");
        pixel->rgb = spher->rgb;
        pixel->t = abc.t2;
        pixel->cor = spher->coord_sph_centr;
        pixel->specular = spher->specular;
        pixel->reflective = spher->reflective;
        //return (t2);
    } 
    return (0.0);  
}



double ClosestIntersection(t_all_obj *all_obj,t_xyz o, t_xyz v)
{
    //double t = MAX_DB;
    t_pixel pixel;

    pixel.t = MAX_DB;
    t_kf_abc abc;

    //t_xyz o;
    t_xyz d;
    t_xyz c;
    t_xyz oc;

    d = v; 

    t_list *sp;
    t_sphere *spher;

    sp = all_obj->sphere;

    //printf("Hello\n");
    while (sp)
    {
                spher = sp->content;
                c  =   spher->coord_sph_centr;

                oc = ft_xyz_minus(o,c);    
                abc.a = ft_xyz_mult_xyz(d,d);
                abc.b = 2 * ft_xyz_mult_xyz(oc,d);
                abc.c = ft_xyz_mult_xyz(oc,oc) - pow(spher->diametr ,2);
                
                ft_intersect_ray_sphere(o,d,&pixel,spher,0.0001,0.99);
                //ft_quadrat_equat(abc.a,abc.b,abc.c,&pixel,spher,0.0001,1.0);
                //ft_quadrat_equat2(k1,k2,k3,&pixel,spher);

                sp = sp->next;
    }
    return (pixel.t);
}

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/



double  ft_compute_lighting_sp(t_all_obj *all_obj,t_xyz p, t_xyz n,t_xyz v,int s)
{
    double i;
    double n_don_l;
    double r_dot_v;
    t_xyz l;
    t_list *light_all;
    t_light *li;
    t_xyz r;   

    i = all_obj->al.light;
    //printf("p  x:%f y:%f z: %f\n",p.x,p.y,p.z);
    //printf("n  x:%f y:%f z: %fs\n",n.x,n.y,n.z);
    light_all = all_obj->light;
    while(light_all)
    {
        li = light_all->content;
        l =  ft_xyz_minus(li->cord_l_point,p);
        if (li->rgb.red == 245)
        {
            l = li->cord_l_point;
        }

        n_don_l = ft_xyz_mult_xyz(n,l);

        //ClosestIntersection
        // проверяем доходит ли цвет
        if (ClosestIntersection(all_obj,p,l) != MAX_DB)
        {
            light_all = light_all->next;
            continue;
        }
        // просто цвет
        if (n_don_l > 0.0)
        {
            i +=  li->light_brightness * n_don_l /( ft_len_vect(n) * ft_len_vect(l));
        }

        // отражения
        if (s > 0)
        {
            r = ft_xyz_mult(n,2.0);
            r = ft_xyz_mult(r,ft_xyz_mult_xyz(n,l));
            r = ft_xyz_minus(r,l);
            //r = ft_xyz_div_doub( ft_xyz_mult( 2*ft_xyz_mult_xyz(n,l));
            r_dot_v = ft_xyz_mult_xyz(r, v);
            if (r_dot_v > 0.0)
                    i += li->light_brightness * pow(r_dot_v/(ft_len_vect(r) * ft_len_vect(v)), s);
        }

        light_all = light_all->next;
    }    
    return (i);
}




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

/*
**  Vectors 
**  point a anb b
**  vector ab = b - a
*/


/*
**  ft_ray_trace
**  
**  
**
**  return (int) color in pixel
*/

/*t_rgb     ft_ray_trace2(t_all_obj *all_obj, t_xyz o, t_xyz v,double t_min,double t_max,int rec)
{
    (void) t_min;
    (void) t_max;
    t_xyz d;
    //t_xyz c;
    t_list *sp;
    t_sphere *spher;
   // t_xyz oc;

    t_xyz p;
    t_xyz n;
    
    //t_kf_abc abc;
    //double k1;
    //double k2;
    //double k3;
    double kf;

    sp = all_obj->sphere;
   // o = ft_create_xyz(all_obj->camera.coord_pointer.x,all_obj->camera.coord_pointer.y,all_obj->camera.coord_pointer.z);
    d = ft_xyz_minus(v,o);
                   
    t_pixel pixel;
    pixel.t = MAX_DB;
    pixel.rgb = all_obj->al.rgb;
    
    while (sp)
    {
            spher = sp->content;
            ft_intersect_ray_sphere(o,d,&pixel,spher,0.0,MAX_DB);
            sp = sp->next;
    }
    if (pixel.t == MAX_DB)
        return (pixel.rgb);

    p = ft_xyz_plus(o,ft_xyz_mult(d,pixel.t));
    n = ft_xyz_minus(p,pixel.cor);
    n = ft_xyz_div_doub(n,ft_len_vect(n));

    kf = ft_compute_lighting_sp(all_obj,p,n,ft_xyz_mult(d,-1.0),pixel.specular);
    pixel.rgb = ft_rgb_mult_db(pixel.rgb,kf);

    if (rec <= 0)
        return (pixel.rgb);
    t_xyz r;
    r = ft_reflect_ray(ft_xyz_mult(d,-1.0),n);

    t_pixel pixel2;
    pixel2.t = MAX_DB;
    pixel2.rgb = all_obj->al.rgb;
    t_rgb ref_color;
    ref_color = ft_ray_trace2(all_obj,p,r,0.00001,MAX_DB,rec - 1);

    t_rgb new;
    new = ft_rgb_mult_db(pixel.rgb,1.0 - 0.3);
    new = ft_rgb_plus_rgb(new, ft_rgb_mult_db(ref_color,0.3));
    return (new);
    //return ( create_rgb(new.red,new.green,new.blue) );
 
}*/

/*
int     ft_ray_trace(t_all_obj *all_obj, double x, double y,int rec)
{
    t_xyz v;
    t_xyz o;
    t_xyz d;
    //t_xyz c;
    t_list *sp;
    t_sphere *spher;
   // t_xyz oc;
    (void) rec;
    t_xyz p;
    t_xyz n;
    
    //t_kf_abc abc;
    //double k1;
    //double k2;
    //double k3;
    double kf;

    sp = all_obj->sphere;
    o = ft_create_xyz(all_obj->camera.coord_pointer.x,all_obj->camera.coord_pointer.y,all_obj->camera.coord_pointer.z);
    v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1.0);
    d = ft_xyz_minus(v,o);
                   
    t_pixel pixel;
    pixel.t = MAX_DB;
    pixel.rgb = all_obj->al.rgb;
    
    while (sp)
    {
            spher = sp->content;
            ft_intersect_ray_sphere(o,d,&pixel,spher,0.0,MAX_DB);
            sp = sp->next;
    }
    if (pixel.t == MAX_DB)
        return (create_rgb(pixel.rgb.red,pixel.rgb.green,pixel.rgb.blue));

    p = ft_xyz_plus(o,ft_xyz_mult(d,pixel.t));
    n = ft_xyz_minus(p,pixel.cor);
    n = ft_xyz_div_doub(n,ft_len_vect(n));

    kf = ft_compute_lighting_sp(all_obj,p,n,ft_xyz_mult(d,-1.0),pixel.specular);
    pixel.rgb = ft_rgb_mult_db(pixel.rgb,kf);
    //return (create_rgb(pixel.rgb.red,pixel.rgb.green,pixel.rgb.blue));
    if (rec <= 0)
        return (create_rgb(pixel.rgb.red,pixel.rgb.green,pixel.rgb.blue));
    //printf("!!\n");    
    t_xyz r;
    r = ft_reflect_ray(ft_xyz_mult(d,-1.0),n);

    t_pixel pixel2;
    pixel2.t = MAX_DB;
    pixel2.rgb = all_obj->al.rgb;
    t_rgb ref_color;
    ref_color = ft_ray_trace2(all_obj,p,r,0.00001,MAX_DB,rec - 1);

    t_rgb new;
    new = ft_rgb_mult_db(pixel.rgb,1.0 - 0.5);
    new = ft_rgb_plus_rgb(new, ft_rgb_mult_db(ref_color,0.5));
    return ( create_rgb(new.red,new.green,new.blue) );
}*/


t_rgb     ft_ray_trace(t_all_obj *all_obj,t_xyz o,t_xyz d,double t_min,double t_max,int rec)
{
    double kf;

    t_list *sp;
    t_sphere *spher;

    t_xyz p;
    t_xyz n;

    t_pixel pixel;
    pixel.t = MAX_DB;
    pixel.rgb = all_obj->al.rgb;
    //pixel.t_min = t_min;
    //pixel.t_max = t_max;
    
    sp = all_obj->sphere;
    while (sp)
    {
            spher = sp->content;
            ft_intersect_ray_sphere(o,d,&pixel,spher,t_min,t_max);
            sp = sp->next;
    }
    if (pixel.t == MAX_DB)
        return (pixel.rgb);
        //return (create_rgb(pixel.rgb.red,pixel.rgb.green,pixel.rgb.blue));
    p = ft_xyz_plus(o,ft_xyz_mult(d,pixel.t));
    n = ft_xyz_minus(p,pixel.cor);
    n = ft_xyz_div_doub(n,ft_len_vect(n));
    kf = ft_compute_lighting_sp(all_obj,p,n,ft_xyz_mult(d,-1.0),pixel.specular);
    pixel.rgb = ft_rgb_mult_db(pixel.rgb,kf);
    //return (create_rgb(pixel.rgb.red,pixel.rgb.green,pixel.rgb.blue));       
    //return(pixel.rgb); 
    if (rec <=  0 )
        return(pixel.rgb);
    t_xyz r;
    r = ft_reflect_ray(ft_xyz_mult(d,-1.0),n);

    t_pixel pixel2;
    pixel2.t = MAX_DB;
    pixel2.rgb = all_obj->al.rgb;
    t_rgb ref_color;
    ref_color = ft_ray_trace(all_obj,p,r,0.001,MAX_DB,rec - 1);
    t_rgb new;
    new = ft_rgb_mult_db(pixel.rgb,1.0 - pixel.reflective);
    new = ft_rgb_plus_rgb(new, ft_rgb_mult_db(ref_color,pixel.reflective));
    return(new);
    //return ( create_rgb(new.red,new.green,new.blue) );    
}

t_xyz ft_new_d(t_xyz r, t_xyz u,t_xyz n , t_xyz d)
{
    t_xyz res;

    res.x = r.x * d.x + r.y * d.y + r.z * d.z;
    res.y = u.x * d.x + u.y * d.y + u.z * d.z;
    res.z = n.x * d.x + n.y * d.y + n.z * d.z;

    return (res);

}
t_xyz   ft_xyz_mult_xyz1(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z; 
    res.z = a.x *  b.y - a.y * b.x;  

    return(res);
}
int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    int cx;
    int cy;
    int color;
    double x;
    double y;
    t_rgb rgb;
    
    
    t_xyz o;
    t_xyz v;
    t_xyz d;
    //t_xyz v_r;
    t_xyz v_up;
    t_xyz c_r;
    t_xyz c_up;

   



    cx = 0;
    cy = 0;
    while (cy < all_obj->reso.height)
    {
        while(cx < all_obj->reso.width)
        {
            x = ft_convert_scr_to_dec_x(cx,all_obj->reso.width,-(all_obj->reso.width/2),all_obj->reso.width/2);
            y = ft_convert_scr_to_dec_y(cy,all_obj->reso.height,-(all_obj->reso.height/2),all_obj->reso.height/2);
            
            o = ft_create_xyz(all_obj->camera.coord_pointer.x,all_obj->camera.coord_pointer.y,all_obj->camera.coord_pointer.z);
            v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1);
            d = ft_xyz_minus(v,o);

            v_up.x = 0.0;
            v_up.y = 1.0;
            v_up.z = 0.0;

            c_r = ft_xyz_mult_xyz1(v_up,all_obj->camera.normal_orientr_vec);
            //c_r = ft_xyz_div_doub(c_r,ft_len_vect(c_r));

            c_up = ft_xyz_mult_xyz1(all_obj->camera.normal_orientr_vec,c_r);
            t_xyz new_d = ft_new_d(c_r,c_up,all_obj->camera.normal_orientr_vec,v);

            rgb = ft_ray_trace(all_obj, o, new_d , 1.0 ,MAX_DB,1);
            color = create_rgb(rgb.red,rgb.green,rgb.blue);
            //color = ft_ray_trace(all_obj,x,y,2);
            mlx_pixel_put(vars->mlx,vars->win,cx,cy,color);
            cx++;
        }
        cx = 0;
        cy++;
    }
    return (1);
}
