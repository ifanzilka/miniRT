/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:52:07 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 22:46:04 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

static void	ft_copy_param(t_param_cy *par, t_pixel *pixel,
		t_cylinder *cy, double t)
{
	pixel->t = t;
	pixel->rgb = cy->rgb;
	pixel->normal = par->n;
	pixel->specular = cy->specular;
	pixel->reflective = -1;
	pixel->id = cylinder;
}

static void	ft_init_mpn(t_param_cy *par, t_cylinder *cy, double t)
{
	par->m = ft_xyz_scal(par->d, cy->normal) * t +
		ft_xyz_scal(par->oc, cy->normal);
	par->p = ft_xyz_plus(par->o, ft_xyz_mult_db(par->d, t * 0.999));
	par->n = ft_xyz_minus(par->p, par->minp);
	par->n = ft_xyz_minus(par->n, ft_xyz_mult_db(cy->normal, par->m));
	par->n = ft_xyz_normalaze(par->n);
}

static void	ft_init_par(t_param_cy *par, t_cylinder *cy)
{
	par->minp = ft_xyz_minus(cy->cord, ft_xyz_mult_db(cy->normal
				, cy->height / 2.0));
	par->maxp = ft_xyz_plus(cy->cord, ft_xyz_mult_db(cy->normal,
				cy->height / 2.0));
	par->oc = ft_xyz_minus(par->o, par->minp);
	par->a = ft_xyz_scal(par->d, par->d) -
		pow(ft_xyz_scal(par->d, cy->normal), 2);
	par->c = ft_xyz_scal(par->oc, par->oc) - pow(ft_xyz_scal(par->oc,
				cy->normal), 2) - pow(cy->diameter / 2.0, 2);
	par->b = 2 * (ft_xyz_scal(par->d, par->oc) - ft_xyz_scal(par->d,
				cy->normal) * ft_xyz_scal(par->oc, cy->normal));
}

void		ft_intersect_cy(t_lutch luc, t_pixel *pixel,
				t_range *range, t_cylinder *cy)
{
	t_param_cy	par;

	par.o = luc.o;
	par.d = luc.d;
	ft_init_par(&par, cy);
	if ((par.discr = par.b * par.b - 4 * par.a * par.c) < 0.0)
		return ;
	par.t1 = (-par.b + sqrt(par.discr)) / (2 * par.a);
	par.t2 = (-par.b - sqrt(par.discr)) / (2 * par.a);
	if (par.t2 < pixel->t && ft_in_range(range, par.t1))
	{
		ft_init_mpn(&par, cy, par.t1);
		if (!(par.m < 0 || par.m > cy->height))
			ft_copy_param(&par, pixel, cy, par.t2);
	}
	if (par.t1 < pixel->t && ft_in_range(range, par.t2))
	{
		ft_init_mpn(&par, cy, par.t2);
		if (!(par.m < 0 || par.m > cy->height))
			ft_copy_param(&par, pixel, cy, par.t1);
	}
}

void		ft_l_cy(t_rt *rt, t_pixel *pixel, t_lutch luc, t_range *range)
{
	t_list		*l_cy;
	t_cylinder	*cy;

	l_cy = rt->l_cy;
	while (l_cy)
	{
		cy = l_cy->content;
		ft_intersect_cy(luc, pixel, range, cy);
		l_cy = l_cy->next;
	}
}
