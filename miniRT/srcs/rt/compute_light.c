/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:34:03 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 17:57:05 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

static void		ft_add_color_li_sp(t_cp_l *cp_l,
		t_xyz *v, t_light *li, t_xyz *n)
{
	if (cp_l->n_dot_l > 0.1)
	{
		cp_l->i = li->intensive * cp_l->n_dot_l /
			(ft_len_vect(*n) * ft_len_vect(cp_l->l));
		cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,
				ft_rgb_mult_db(li->rgb, cp_l->i));
	}
	if (cp_l->spec > 1)
	{
		cp_l->r = ft_reflect_ray(cp_l->l, *n);
		cp_l->r_dot_v = ft_xyz_scal(cp_l->r, *v);
		if (cp_l->r_dot_v > 0.0)
		{
			cp_l->i = li->intensive * pow(cp_l->r_dot_v /
					(ft_len_vect(cp_l->r) * ft_len_vect(*v)), cp_l->spec);
			cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,
					ft_rgb_mult_db(li->rgb, cp_l->i));
		}
	}
}

static void		ft_init_color(t_rt *rt, t_cp_l *cp_l, t_pixel *pixel)
{
	cp_l->color_pix = ft_rgb_mult_db(pixel->rgb, rt->al.light);
	cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,
			ft_rgb_mult_db(rt->al.rgb, rt->al.light));
	cp_l->spec = pixel->specular;
}

static void		ft_init_vectors_light(t_light *li, t_cp_l *cp_l,
		t_pixel *pixel, t_xyz *n)
{
	cp_l->l = ft_xyz_minus(li->cord, pixel->p);
	cp_l->n_dot_l = ft_xyz_scal(*n, cp_l->l);
	if (cp_l->n_dot_l <= 0.0 && (pixel->id == plane || pixel->id == triangle))
	{
		*n = ft_xyz_mult_db(*n, -1.0);
		cp_l->n_dot_l *= -1.0;
	}
}

/*
**  o vec -> point in object
**  d -> vec in light
*/

static double	closestintersection(t_rt *rt, t_xyz o, t_xyz d)
{
	t_pixel	pixel;
	t_range	range;

	range.min = 0.000001;
	range.max = 0.999999;
	pixel.t = MAX_DB;
	ft_iter_obj_close(rt, &pixel, (t_lutch){o, d}, &range);
	return (pixel.t);
}

t_rgb			ft_compute_lighting(t_rt *rt, t_xyz n, t_xyz v, t_pixel *pixel)
{
	t_list	*l_light;
	t_light	*li;
	t_cp_l	*cp_l;

	if (!(cp_l = malloc_gc(sizeof(t_cp_l))))
		ft_error_rt(err_malloc, rt);
	ft_init_color(rt, cp_l, pixel);
	l_light = rt->l_light;
	while (l_light)
	{
		li = l_light->content;
		ft_init_vectors_light(li, cp_l, pixel, &n);
		if (closestintersection(rt, pixel->p, cp_l->l) != MAX_DB)
		{
			l_light = l_light->next;
			continue;
		}
		ft_add_color_li_sp(cp_l, &v, li, &n);
		l_light = l_light->next;
	}
	return (cp_l->color_pix);
}
