/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:04:28 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/30 19:04:29 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray_tracing.h>

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

    
    if (!(pixel = malloc(sizeof(t_pixel))) || !(ft_lst_cr_front(&rt->l_p, pixel)))
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
    //if (pixel->id == triangle)
        //pixel-> normal.z *= -1;// ft_xyz_mult_db(pixel->normal,-1.0);
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel->normal);
    ref_color = ft_ray_trace(rt, p, r,range,rec - 1);  
    return(ft_recurse_color(ref_color, pixel->rgb, pixel->reflective));
}

// t_rgb     ft_ray_trace(t_rt *rt,t_xyz o,t_xyz d,t_range range,int rec)
// {
//     t_xyz   p;
//     t_xyz   r;
//     t_pixel pixel;
//     t_rgb   ref_color;

       
//     pixel.t = MAX_DB;
//     pixel.rgb = ft_rgb_mult_db(rt->al.rgb,rt->al.light);
//     ft_iter_obj(rt, &pixel, o, d,&range);
//     if (pixel.t == MAX_DB)
//         return (pixel.rgb);
//     //pixel.normal = ft_xyz_mult_db(pixel.normal,-1.0);    
//     p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel.t * 0.9999));
//     pixel.rgb = ft_compute_lighting(rt,  p, pixel.normal,ft_xyz_mult_db(d, -1.0),&pixel);
//     if (rec <=  0 || pixel.reflective <= 0.01)
//         return(pixel.rgb);
//     r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel.normal);
//     ref_color = ft_ray_trace(rt, p, r,range,rec - 1);  
//     return(ft_recurse_color(ref_color, pixel.rgb, pixel.reflective));
// }