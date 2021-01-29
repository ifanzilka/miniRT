/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 23:26:25 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/29 23:26:27 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

t_xyz      ft_create_v(double x, double y, int height, double z)
{
    t_xyz v;

    v.x =   x / height;
    v.y =   y / height;
    v.z =   z;
    return (v);
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
