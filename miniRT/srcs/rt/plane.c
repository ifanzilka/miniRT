/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:09:22 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 20:13:50 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

void	ft_intersect_pl(t_lutch luc, t_pixel *pixel,
		t_range *range, t_plane *pl)
{
	double	t;
	double	dn;
	double	on;
	double	dd;

	dd = -ft_xyz_scal(pl->normal, pl->cord);
	dn = ft_xyz_scal(pl->normal, luc.d);
	on = ft_xyz_scal(pl->normal, luc.o) + dd;
	if (dn == 0)
		return ;
	if (fabs(dn) < 0.0000001)
		return ;
	t = -on / dn;
	if (t < pixel->t && ft_in_range(range, t))
	{
		pixel->t = t;
		pixel->rgb = pl->rgb;
		pixel->normal = pl->normal;
		pixel->specular = pl->specular;
		pixel->reflective = pl->reflective;
		pixel->id = plane;
	}
}

void	ft_l_pl(t_rt *rt, t_pixel *pixel, t_lutch luc, t_range *range)
{
	t_list	*l_pl;
	t_plane	*pl;

	l_pl = rt->l_pl;
	while (l_pl)
	{
		pl = l_pl->content;
		ft_intersect_pl(luc, pixel, range, pl);
		l_pl = l_pl->next;
	}
}

/*
**  ft_l_pl
** rt -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/
