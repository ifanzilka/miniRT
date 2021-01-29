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

void ft_iter_obj_close(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_pl(rt, pixel, o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_tr(rt,pixel,o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_sq(rt,pixel,o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_cy(rt,pixel,o, d,range);
}


void ft_iter_obj(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    ft_l_pl(rt, pixel, o, d,range);
    ft_l_tr(rt,pixel,o, d,range);
    ft_l_sq(rt,pixel,o, d,range);
    ft_l_cy(rt,pixel,o, d,range);
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
    ft_iter_obj_close(rt, &pixel, o, d,&range);
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
    //pixel->rgb = ft_compute_lighting(rt,  p, pixel->normal,ft_xyz_mult_db(d, -1.0),pixel);
    if (rec <=  0 || pixel->reflective <= 0.01)
        return(pixel->rgb);
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel->normal);
    ref_color = ft_ray_trace(rt, p, r,range,rec - 1);  
    return(ft_recurse_color(ref_color, pixel->rgb, pixel->reflective));
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
    write(1,"Start Rendering...\n",19);
    while (cy < rt->reso.height)
    {
        while(cx < rt->reso.width)
        {    
            d = ft_init_d(&cx,&cy,rt);
            rgb = ft_ray_trace(rt, rt->camera->cord, d ,(t_range){0.0001,MAX_DB},depth);
            //mlx_pixel_put(vars->mlx,vars->win,cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));   
            my_mlx_pixel_put(&(vars->img),cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            ft_putnbr_fd((int)((double)(cx + cy * rt->reso.width) / (double)(rt->reso.height * rt->reso.width) * 100),1);
            write(1,"%\r",2);
            while(1)
            ;
            cx++;
        }
        cx = 0;
        cy++;
    }
    if (vars->bmp)
        ft_create_bmp(rt,&(vars->img));
    else    
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0); 
    return (1);
}
