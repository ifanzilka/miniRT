/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:49:49 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 22:55:50 by bmarilli         ###   ########.fr       */
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
	t_xyz		o;
	t_xyz		d;
	t_xyz		oc;
}				t_kf_abc;

typedef struct	s_param_tr
{
	t_xyz	v1;
	t_xyz	v2;
	t_xyz	n;
	t_xyz	v1d;
	t_xyz	vec;
	t_xyz	q_vec;
	double	scal_v2_v1d;
	double	t;
	double	u;
	double	v;
}				t_param_tr;

typedef struct	s_param_sq
{
	t_xyz	p;
	t_xyz	n_r;
	t_xyz	n_up;
	t_xyz	a;
	t_xyz	b;
	t_xyz	c;
	t_xyz	d;
	t_xyz	c_d;
	t_xyz	a_b;
	t_xyz	ab;
	t_xyz	bc;
	t_xyz	cd;
	t_xyz	da;
	t_xyz	n_ab;
	t_xyz	n_bc;
	t_xyz	n_cd;
	t_xyz	n_da;
	double	ans;
	double	t;
}				t_param_sq;

typedef struct	s_param_cy
{
	double	a;
	double	b;
	double	c;
	double	discr;
	double	t1;
	double	t2;
	t_xyz	minp;
	t_xyz	maxp;
	t_xyz	o;
	t_xyz	d;
	t_xyz	oc;
	double	m;
	t_xyz	n;
	t_xyz	p;
	t_xyz	p1;
	t_xyz	p2;
}				t_param_cy;

typedef struct	s_lutch
{
	t_xyz	o;
	t_xyz	d;
}				t_lutch;

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
void			ft_intersect_pl(t_lutch luc, t_pixel *pixel,
					t_range *range, t_plane *pl);
void			ft_l_sp(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_l_pl(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_l_tr(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_l_sq(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_l_cy(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_iter_obj_close(t_rt *rt, t_pixel *pixel,
					t_lutch luc, t_range *range);
void			ft_iter_obj(t_rt *rt, t_pixel *pixel, t_lutch lut,
					t_range *range);
t_rgb			ft_compute_lighting(t_rt *rt, t_xyz n,
					t_xyz v, t_pixel *pixel);
t_rgb			ft_ray_trace(t_rt *rt, t_xyz o,
					t_xyz d, int rec);

#endif
