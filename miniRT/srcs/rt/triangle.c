/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:15:26 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 20:37:50 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

static void	ft_copy_pixel(t_pixel *pixel, t_triangle *tr, t_param_tr *par)
{
	pixel->t = par->t;
	pixel->rgb = tr->rgb;
	pixel->normal = par->n;
	pixel->specular = tr->specular;
	pixel->reflective = tr->reflective;
	pixel->id = triangle;
}

static void	ft_intersect_ray_triangle(t_lutch luc, t_pixel *pixel,
		t_triangle *tr, t_range *range)
{
	t_param_tr	par;

	par.v1 = ft_xyz_minus(tr->second, tr->first);
	par.v2 = ft_xyz_minus(tr->third, tr->first);
	par.n = ft_xyz_mult_xyz(par.v1, par.v2);
	par.v1d = ft_xyz_mult_xyz(par.v2, luc.d);
	par.scal_v2_v1d = ft_xyz_scal(par.v1, par.v1d);
	if (fabs(par.scal_v2_v1d) < 0.01)
		return ;
	par.vec = ft_xyz_minus(luc.o, tr->first);
	par.u = ft_xyz_scal(par.vec, par.v1d) / par.scal_v2_v1d;
	if (par.u < 0.0 || par.u > 1.0)
		return ;
	par.q_vec = ft_xyz_mult_xyz(par.v1, par.vec);
	par.v = ft_xyz_scal(luc.d, par.q_vec) / par.scal_v2_v1d;
	if (par.v < 0.0 || par.u + par.v > 1.0)
		return ;
	par.t = ft_xyz_scal(par.v2, par.q_vec) / par.scal_v2_v1d;
	if (par.t < pixel->t && ft_in_range(range, par.t))
		ft_copy_pixel(pixel, tr, &par);
}

void		ft_l_tr(t_rt *rt, t_pixel *pixel, t_lutch luc, t_range *range)
{
	t_list		*l_tr;
	t_triangle	*tr;

	l_tr = rt->l_tr;
	while (l_tr)
	{
		tr = l_tr->content;
		ft_intersect_ray_triangle(luc, pixel, tr, range);
		l_tr = l_tr->next;
	}
}
