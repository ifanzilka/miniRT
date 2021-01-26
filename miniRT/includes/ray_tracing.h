/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:49:49 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/26 18:49:50 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "ft_minirt.h"

typedef struct  s_pixel 
{
    double          t;
    t_rgb           rgb;
    t_xyz           normal;
    int             specular;
    double          reflective;
    int             id;
}               t_pixel;

typedef struct  s_kf_abc 
{
    double          a;
    double          b;
    double          c;
    double          t1;
    double         t2;
    double         discr;
}                t_kf_abc;

int     ft_init_disp(t_all_obj *rt);
int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars);
int     ft_in_range(t_range *range, double a);
void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range *range, t_plane *pl);
void    ft_l_sp(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_pl(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_tr(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_sq(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_cy(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_next_cam(t_vars *vars);
void    ft_prev_cam(t_vars *vars);
void    ft_plus_cam(t_vars *vars);
void    ft_minus_cam(t_vars *vars);
void    ft_right_cam(t_vars *vars);
void    ft_left_cam(t_vars *vars);
void    ft_up_cam(t_vars *vars);
void    ft_down_cam(t_vars *vars);
void    ft_revers_cam(t_vars *vars);
void    ft_plus_al(t_vars *vars);
void    ft_minus_al(t_vars *vars);
#endif