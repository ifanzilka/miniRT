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

#include <ft_minirt.h>

/*
**
**  s_vars 
**  mlx -> pointer libary
**  win -> link for window 
*/

typedef struct  s_vars 
{
    void        *mlx;
    void        *win;
    void        *rt;
}                t_vars;

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

int     ft_init_disp(t_rt *rt);
int     cicle_for_pixel(t_rt *rt,t_vars *vars);
int     ft_in_range(t_range *range, double a);
void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range *range, t_plane *pl);
void    ft_l_sp(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_pl(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_tr(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_sq(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_cy(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);

#endif