/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:42:27 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 21:50:01 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

static void	ft_copy_par(t_param_sq par, t_pixel *pixel,
		t_square *sq, t_range *range)
{
	t_range	range2;

	if (par.t < pixel->t && ft_in_range(range, par.t))
	{
		range2.min = -sq->side / 2;
		range2.max = sq->side / 2;
		if (ft_in_range(&range2, par.p.x - sq->cord.x) && ft_in_range(&range2,
					par.p.y - sq->cord.y) && ft_in_range(&range2,
						par.p.z - sq->cord.z))
		{
			pixel->t = par.t;
			pixel->rgb = sq->rgb;
			pixel->normal = sq->normal;
			pixel->specular = sq->specular;
			pixel->reflective = sq->reflective;
			pixel->id = triangle;
		}
	}
}

static void	ft_check_pl(t_param_sq par, t_pixel *pixel,
		t_square *sq, t_range *range)
{
	par.ans = (par.p.x - par.a.x) * par.n_ab.x + (par.p.y - par.a.y)
		* par.n_ab.y + (par.p.z - par.a.z) * par.n_ab.z;
	par.ans *= (par.d.x - par.a.x) * par.n_ab.x + (par.d.y - par.a.y)
		* par.n_ab.y + (par.p.z - par.a.z) * par.n_ab.z;
	if (par.ans < 0)
		return ;
	par.ans = (par.p.x - par.b.x) * par.n_bc.x + (par.p.y - par.b.y) *
		par.n_bc.y + (par.p.z - par.b.z) * par.n_bc.z;
	par.ans *= (par.a.x - par.b.x) * par.n_bc.x + (par.a.y - par.b.y) *
		par.n_bc.y + (par.a.z - par.b.z) * par.n_bc.z;
	if (par.ans < 0)
		return ;
	par.ans = (par.p.x - par.c.x) * par.n_cd.x + (par.p.y - par.c.y) *
		par.n_cd.y + (par.p.z - par.c.z) * par.n_cd.z;
	par.ans *= (par.a.x - par.c.x) * par.n_cd.x + (par.a.y - par.c.y) *
		par.n_cd.y + (par.a.z - par.c.z) * par.n_cd.z;
	if (par.ans < 0)
		return ;
	par.ans = (par.p.x - par.d.x) * par.n_da.x + (par.p.y - par.d.y) *
		par.n_da.y + (par.p.z - par.d.z) * par.n_da.z;
	par.ans *= (par.b.x - par.d.x) * par.n_da.x + (par.b.y - par.d.y) *
		par.n_da.y + (par.b.z - par.d.z) * par.n_da.z;
	if (par.ans < 0)
		return ;
	ft_copy_par(par, pixel, sq, range);
}

static void	ft_check_square(t_param_sq par, t_pixel *pixel,
		t_square *sq, t_range *range)
{
	par.n_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0}, sq->normal);
	par.n_up = ft_xyz_mult_xyz(sq->normal, par.n_r);
	par.c_d = ft_xyz_plus(sq->cord, ft_xyz_mult_db(par.n_r, sq->side / 2));
	par.a_b = ft_xyz_minus(sq->cord, ft_xyz_mult_db(par.n_r, sq->side / 2));
	par.a = ft_xyz_minus(par.a_b, ft_xyz_mult_db(par.n_up, sq->side / 2));
	par.b = ft_xyz_plus(par.a_b, ft_xyz_mult_db(par.n_up, sq->side / 2));
	par.d = ft_xyz_minus(par.c_d, ft_xyz_mult_db(par.n_up, sq->side / 2));
	par.c = ft_xyz_plus(par.c_d, ft_xyz_mult_db(par.n_up, sq->side / 2));
	par.ab = ft_xyz_minus(par.b, par.a);
	par.bc = ft_xyz_minus(par.c, par.b);
	par.cd = ft_xyz_minus(par.d, par.c);
	par.da = ft_xyz_minus(par.a, par.d);
	par.n_ab = ft_xyz_mult_xyz(par.ab, sq->normal);
	par.n_bc = ft_xyz_mult_xyz(par.bc, sq->normal);
	par.n_cd = ft_xyz_mult_xyz(par.cd, sq->normal);
	par.n_da = ft_xyz_mult_xyz(par.da, sq->normal);
	par.ans = 0;
	ft_check_pl(par, pixel, sq, range);
}

void		ft_intersect_ray_square(t_lutch luc, t_pixel *pixel,
				t_square *sq, t_range *range)
{
	t_pixel		pixel_loc;
	t_plane		pl;
	t_xyz		o;
	t_xyz		dir;
	t_param_sq	par;

	o = luc.o;
	dir = luc.d;
	pixel_loc.t = MAX_DB;
	pl.normal = sq->normal;
	pl.cord = sq->cord;
	ft_intersect_pl(luc, &pixel_loc, range, &pl);
	if (pixel_loc.t == MAX_DB)
		return ;
	par.t = pixel_loc.t;
	par.p = ft_xyz_plus(o, ft_xyz_mult_db(dir, pixel_loc.t * 0.999));
	ft_check_square(par, pixel, sq, range);
}

void		ft_l_sq(t_rt *rt, t_pixel *pixel, t_lutch luc, t_range *range)
{
	t_list		*l_sq;
	t_square	*sq;

	l_sq = rt->l_sq;
	while (l_sq)
	{
		sq = l_sq->content;
		ft_intersect_ray_square(luc, pixel, sq, range);
		l_sq = l_sq->next;
	}
}
