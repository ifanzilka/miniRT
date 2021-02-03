/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:49:01 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 19:33:40 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

/*
**  Sphere:
** P - point lutch
** C - Center sphere
**
** |P - C| = r
**
**  <P - C, P - C > = r ^ 2
**
** D = V - O
**
** and  P = O + t * D*
*/

static int	ft_sphere(t_kf_abc abc, t_pixel *pixel,
		t_sphere *spher, t_range *range)
{
	t_xyz	p;
	t_xyz	n;

	if ((abc.t1 < abc.t2) && (abc.t1 < pixel->t) && ft_in_range(range, abc.t1))
	{
		pixel->rgb = spher->rgb;
		pixel->t = abc.t1;
		pixel->specular = spher->specular;
		pixel->reflective = spher->reflective;
		p = ft_xyz_plus(abc.o, ft_xyz_mult_db(abc.d, pixel->t));
		n = ft_xyz_minus(p, spher->coord_sph_centr);
		pixel->normal = n;
		return (1);
	}
	if ((abc.t2 <= abc.t1) && (abc.t2 < pixel->t) && ft_in_range(range, abc.t2))
	{
		pixel->rgb = spher->rgb;
		pixel->t = abc.t2;
		pixel->specular = spher->specular;
		pixel->reflective = spher->reflective;
		p = ft_xyz_plus(abc.o, ft_xyz_mult_db(abc.d, pixel->t));
		n = ft_xyz_minus(p, spher->coord_sph_centr);
		pixel->normal = n;
	}
	return (0);
}

static int	ft_in_sphere(t_kf_abc abc, t_pixel *pixel,
		t_sphere *spher, t_range *range)
{
	t_xyz	p;
	t_xyz	n;

	if ((abc.t1) < pixel->t && ft_in_range(range, abc.t1))
	{
		pixel->rgb = spher->rgb;
		pixel->t = abc.t1;
		pixel->specular = spher->specular;
		p = ft_xyz_plus(abc.o, ft_xyz_mult_db(abc.d, pixel->t * 0.9999));
		n = ft_xyz_minus(spher->coord_sph_centr, p);
		pixel->normal = n;
		return (1);
	}
	else if ((abc.t2 < pixel->t) && ft_in_range(range, abc.t2))
	{
		pixel->rgb = spher->rgb;
		pixel->t = abc.t2;
		pixel->specular = spher->specular;
		p = ft_xyz_plus(abc.o, ft_xyz_mult_db(abc.d, pixel->t * 0.9999));
		n = ft_xyz_minus(spher->coord_sph_centr, p);
		pixel->normal = n;
		return (1);
	}
	return (0);
}

static int	ft_check_t1_t2(t_kf_abc abc, t_pixel *pixel,
		t_sphere *spher, t_range *range)
{
	if ((ft_in_range(range, abc.t1)) || (!ft_in_range(range, abc.t2)))
	{
		if ((abc.t1 >= 0.0 && abc.t2 <= 0.0) ||
				(abc.t2 >= 0.0 && abc.t1 <= 0.0))
			return (ft_in_sphere(abc, pixel, spher, range));
		return (ft_sphere(abc, pixel, spher, range));
	}
	return (0);
}

double		ft_intersect_ray_sphere(t_lutch luc, t_pixel *pixel,
		t_sphere *spher, t_range *range)
{
	t_xyz		oc;
	t_kf_abc	abc;

	oc = ft_xyz_minus(luc.o, spher->coord_sph_centr);
	abc.oc = oc;
	abc.a = ft_xyz_scal(luc.d, luc.d);
	abc.b = 2 * ft_xyz_scal(oc, luc.d);
	abc.c = ft_xyz_scal(oc, oc) - pow(spher->diametr, 2);
	abc.o = luc.o;
	abc.d = luc.d;
	if ((abc.discr = abc.b * abc.b - 4 * abc.a * abc.c) < 0.0)
		return (MAX_DB);
	abc.t1 = (-abc.b + sqrt(abc.discr)) / (2 * abc.a);
	abc.t2 = (-abc.b - sqrt(abc.discr)) / (2 * abc.a);
	ft_check_t1_t2(abc, pixel, spher, range);
	return (0.0);
}

/*
**  ft_l_sphere
**  rt -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/

void		ft_l_sp(t_rt *rt, t_pixel *pixel, t_lutch luh, t_range *range)
{
	t_list		*l_sp;
	t_sphere	*spher;

	l_sp = rt->l_sphere;
	while (l_sp)
	{
		spher = l_sp->content;
		ft_intersect_ray_sphere(luh, pixel, spher, range);
		l_sp = l_sp->next;
	}
}
