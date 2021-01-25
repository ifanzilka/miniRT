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
#include "ray_tracing.h"



int     ft_in_range(t_range *range, double a)
{
    if (a >= range->min && a <= range->max)
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
**  o vec -> point in obk=ject
**  d -> vec in light
**
**
*/

double ClosestIntersection(t_all_obj *all_obj,t_xyz o, t_xyz d)
{
    t_pixel pixel;
    t_range range;

    range.min = 0.000001;
    range.max = 0.999999;
    pixel.t = MAX_DB;
    ft_l_sp(all_obj, &pixel, o, d,&range);
    ft_l_pl(all_obj, &pixel, o, d,&range);
    ft_l_tr(all_obj,&pixel,o, d,&range);
    ft_l_sq(all_obj,&pixel,o, d,&range);
    ft_l_cy(all_obj,&pixel,o, d,&range);
    return (pixel.t);
}

/*
**   ft_compute_lighting
**  all_object
**  point (p) in object
**  n -> normal vec
**  v -> vec in (-d)
*/


t_rgb  ft_compute_lighting(t_all_obj *all_obj,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
{
    (void) v;
    double i;
    double n_don_l;
    double r_dot_v;
    t_xyz l;
    t_list *l_light;
    t_light *li;
    t_xyz r;

    t_rgb	color_pix = {0,0,0};
    
    color_pix = ft_rgb_mult_db(all_obj->al.rgb,all_obj->al.light);
	color_pix = ft_rgb_plus_rgb(color_pix, ft_rgb_mult_db(pixel->rgb,all_obj->al.light));
    l_light = all_obj->l_light;
    while(l_light)
    {
        li = l_light->content;
        l =  ft_xyz_minus(li->cord_l_point,p);
        n = ft_xyz_normalaze(n);
        //l = ft_xyz_normalaze(l);
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
        if (n_don_l > 0.0 )
        {
            i =  li->light_brightness * n_don_l /( ft_len_vect(n) * ft_len_vect(l));
            color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
        }

            if (pixel->specular > -10)
            {
                //r = ft_reflect_ray(n,l);
                //r = ft_reflect_ray(ft_xyz_mult_db(v,1.0),n);
                r = ft_xyz_mult_db(n,2.0);
                r = ft_xyz_mult_db(r,ft_xyz_scal(n,l));
                r = ft_xyz_minus(r,l);
                r_dot_v = ft_xyz_scal(r, v);
                //printf("n : x:%f y:%f z:%f\n",n.x,n.y,n.z);
                //printf("l : x:%f y:%f z:%f\n",l.x,l.y,l.z);
                //printf("r : x: %f y:%f z:%f \n",r.x,r.y,r.z);
            
                if (r_dot_v > 0.0)
                {
                        i = li->light_brightness * pow(r_dot_v/(ft_len_vect(r) * ft_len_vect(v)),100);
                        color_pix = ft_rgb_plus_rgb(color_pix,ft_rgb_mult_db(li->rgb,i));
                }
            }
        l_light = l_light->next;
    }    
    return (color_pix);
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
    ft_l_sp(all_obj, &pixel, o, d,&range);
    ft_l_pl(all_obj, &pixel, o, d,&range);
    ft_l_tr(all_obj,&pixel,o, d,&range);
    ft_l_sq(all_obj,&pixel,o, d,&range);
    ft_l_cy(all_obj,&pixel,o, d,&range);
    if (pixel.t == MAX_DB)
        return (pixel.rgb);
    p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel.t * 0.9999));
    pixel.rgb = ft_compute_lighting(all_obj,  p, pixel.normal,ft_xyz_mult_db(d, -1.0),&pixel);
    if (rec <=  0 || pixel.reflective <= 0.01)
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
    //all_obj->camera.camera_direction = ft_xyz_normalaze(all_obj->camera.camera_direction);
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
