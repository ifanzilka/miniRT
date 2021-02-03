/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:49:49 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 20:14:47 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include <ft_minirt.h>
# include <mlx_win.h>

typedef struct	s_pixel
{
	double		t;
	t_rgb		rgb;
	t_xyz		normal;
	t_xyz		p;
	int			specular;
	double		reflective;
	int			id;
}				t_pixel;

typedef struct	s_kf_abc
{
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;
	double		discr;
}				t_kf_abc;

/*
**   ft_compute_lighting
**  rtect
**  point (p) in object
**  n -> normal vec
**  v -> vec in (-d)
*/

typedef struct	s_cp_l
{
	double		i;
	double		n_dot_l;
	double		r_dot_v;
	t_rgb		color_pix;
	t_xyz		l;
	t_xyz		r;
	int			spec;
}				t_cp_l;

void			ft_percent_render(int x, int y, int width,
					int height);
double			ft_convert_scr_to_dec_x(int cx, int width,
					double xmin, double xmax);
double			ft_convert_scr_to_dec_y(int cy, int height,
					double ymin, double ymax);
void			ft_rt_xy_convert(int *cx, int *cy,
					double *x, double *y, t_rt *rt);
t_xyz			ft_create_v(double x, double y,
					int height, double z);
t_xyz			ft_init_d(int *cx, int *cy, t_rt *rt);
int				cicle_for_pixel(t_rt *rt, t_vars *vars);
int				ft_in_range(t_range *range, double a);
void			ft_intersect_pl(t_xyz o, t_xyz d, t_pixel *pixel,
					t_range *range, t_plane *pl);
void			ft_l_sp(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_l_pl(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_l_tr(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_l_sq(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_l_cy(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_iter_obj_close(t_rt *rt, t_pixel *pixel, t_xyz o,
					t_xyz d, t_range *range);
void			ft_iter_obj(t_rt *rt, t_pixel *pixel, t_xyz o, t_xyz d,
					t_range *range);
t_rgb			ft_compute_lighting(t_rt *rt, t_xyz n,
					t_xyz v, t_pixel *pixel);
t_rgb			ft_ray_trace(t_rt *rt, t_xyz o,
					t_xyz d, int rec);

#endif
