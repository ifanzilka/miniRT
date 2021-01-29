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

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct  s_vars 
{
    t_img       img;
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

/*
**   ft_compute_lighting
**  rtect
**  point (p) in object
**  n -> normal vec
**  v -> vec in (-d)
*/

typedef struct s_cp_l
{
    double      i;
    double      n_dot_l;
    double      r_dot_v; 
    t_rgb       color_pix;
    t_xyz       l;    
    t_xyz       r;
}              t_cp_l;

void            my_mlx_pixel_put(t_img *img, int x, int y, int color);
void        ft_create_bmp(t_rt *rt,t_img *img);
int     ft_init_disp(t_rt *rt);
int     ft_init_img(t_rt *rt);
int     cicle_for_pixel(t_rt *rt,t_vars *vars);
int     cicle_for_pixel_sc(t_rt *rt,t_vars *vars);
int     ft_in_range(t_range *range, double a);
void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range *range, t_plane *pl);
void    ft_l_sp(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_pl(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_tr(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_sq(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
void    ft_l_cy(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range);
double ClosestIntersection(t_rt *rt,t_xyz o, t_xyz d);
t_rgb  ft_compute_lighting(t_rt *rt,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel);


#endif