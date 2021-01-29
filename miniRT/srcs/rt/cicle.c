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
#include "ray_tracing.h"
# ifndef depth
#define depth 0
#endif

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

void  ft_rt_xy_convert(int *cx,int *cy, double *x,double *y,t_rt *rt)
{
    double width;
    double height;

    width = rt->reso.width;
    height = rt->reso.height;
     *x =  ft_convert_scr_to_dec_x(*cx, width, -(width / 2), width / 2);
     *y =  ft_convert_scr_to_dec_y(*cy, height, -(height / 2),height / 2);
}

void ft_iter_obj(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    ft_l_pl(rt, pixel, o, d,range);
    ft_l_tr(rt,pixel,o, d,range);
    ft_l_sq(rt,pixel,o, d,range);
    ft_l_cy(rt,pixel,o, d,range);
}

t_xyz      ft_create_v(double x, double y, int height, double z)
{
    t_xyz v;

    v.x =   x / height;
    v.y =   y / height;
    v.z =   z;
    return (v);
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

double ClosestIntersection(t_rt *rt,t_xyz o, t_xyz d)
{
    t_pixel pixel;
    t_range range;

    range.min = 0.000001;
    range.max = 0.999999;
    pixel.t = MAX_DB;
    ft_iter_obj(rt, &pixel, o, d,&range);
    return (pixel.t);
}


/*
**  ft_ray_trace
**  rt -> struct in rt
**  vec o -> point start in lutch (camera)
**  vec d -> lutch in ray_trace
**  range -> min and max kf for d 
**  p = o + D * t 
**  return (rgb) color in pixel
*/

t_rgb     ft_ray_trace(t_rt *rt,t_xyz o,t_xyz d,t_range range,int rec)
{
    t_xyz   p;
    t_xyz   r;
    t_pixel *pixel;
    t_rgb   ref_color;

    if (!(pixel = malloc(sizeof(t_pixel))) && !(ft_lst_cr_front(&rt->l_p, pixel)))
        ft_error_rt(err_malloc,rt);
    pixel->t = MAX_DB;
    pixel->rgb = ft_rgb_mult_db(rt->al.rgb,rt->al.light);
    ft_iter_obj(rt, pixel, o, d,&range);
    if (pixel->t == MAX_DB)
        return (pixel->rgb);
    //pixel.normal = ft_xyz_mult_db(pixel.normal,-1.0);    
    p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel->t * 0.9999));
    pixel->rgb = ft_compute_lighting(rt,  p, pixel->normal,ft_xyz_mult_db(d, -1.0),pixel);
    if (rec <=  0 || pixel->reflective <= 0.01)
        return(pixel->rgb);
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel->normal);
    ref_color = ft_ray_trace(rt, p, r,range,rec - 1);
    return(ft_recurse_color(ref_color, pixel->rgb, pixel->reflective));
}

t_xyz   ft_create_vec_d(t_rt *rt, double x, double y)
{
    t_xyz   c_r;
    t_xyz   c_up;
    t_xyz   d;
    t_xyz   v;
    double  kf;
    
    rt->camera->direction = ft_xyz_normalaze(rt->camera->direction);
    kf  =  2 * tan(rt->camera->fov / 2 * 3.14 / 180);
    x *= kf;
    y *= kf;
    v = ft_create_v(x, y, rt->reso.height, 1);
    c_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0},rt->camera->direction);
    c_up = ft_xyz_mult_xyz(rt->camera->direction,c_r);
    d = ft_r_u_n_mult_xyz(c_r,c_up,rt->camera->direction,v);
    return (d);
}

t_xyz ft_init_d(int *cx,int *cy,t_rt *rt)
{
    double x;
    double y;

    ft_rt_xy_convert(cx,cy,&x,&y,rt);
    return (ft_create_vec_d(rt , x ,y));
}

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/


int     cicle_for_pixel(t_rt *rt,t_vars *vars)
{
    int cx;
    int cy;
    t_rgb rgb;
    t_xyz d;

    cx = 0;
    cy = 0;
    while (cy < rt->reso.height)
    {
        while(cx < rt->reso.width)
        {    
            d = ft_init_d(&cx,&cy,rt);
            rgb = ft_ray_trace(rt, rt->camera->cord, d ,(t_range){0.0001,MAX_DB},depth);
            my_mlx_pixel_put(&(vars->img),cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            ft_putnbr_fd((int)((double)(cx + cy * rt->reso.width) / (double)(rt->reso.height * rt->reso.width) * 100),1);
            write(1,"%\r",2);
            cx++;
        }
        cx = 0;
        cy++;
    }
     mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0); 
    return (1);
}
int     cicle_for_pixel_sc(t_rt *rt,t_vars *vars)
{
    int cx;
    int cy;
    t_rgb rgb;
    t_xyz d;

    cx = 0;
    cy = 0;
    printf("ok");
    while (cy < rt->reso.height)
    {
        while(cx < rt->reso.width)
        {    
            d = ft_init_d(&cx,&cy,rt);
            rgb = ft_ray_trace(rt, rt->camera->cord, d ,(t_range){0.0001,MAX_DB},depth);
            my_mlx_pixel_put(&(vars->img),cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            ft_putnbr_fd((int)((double)(cx + cy * rt->reso.width) / (double)(rt->reso.height * rt->reso.width) * 100),1);
            write(1,"%\r",2);
            cx++;
        }
        cx = 0;
        cy++;
    }
     ft_create_bmp(rt,&(vars->img));
    return (1);
}
