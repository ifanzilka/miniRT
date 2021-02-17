/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:04:28 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/18 02:13:13 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray_tracing.h>

/*
**   ft_recurse_color
**
**   return local_color * (1 - r) + reflected_color * r
*/

t_rgb	ft_recurse_color(t_rgb ref_col, t_rgb loc_col, double reflective)
{
	t_rgb	res;

	res = ft_rgb_mult_db(loc_col, 1 - reflective);
	res = ft_rgb_plus_rgb(res, ft_rgb_mult_db(ref_col, reflective));
	return (res);
}

/*
**  ft_ray_trace
**  rt -> struct in rt
**  vec o -> point start in lutch (camera)
**  vec d -> lutch in ray_trace
**  range -> min and max kf for d
**  p = o + D * t
**  return (rgb) color in pixel
*/

t_rgb	ft_ray_trace(t_rt *rt, t_xyz o, t_xyz d, int rec)
{
	t_xyz	r;
	t_pixel	*pixel;
	t_rgb	ref_color;

	if (!(pixel = malloc(sizeof(t_pixel))))
		ft_error_rt(err_malloc, rt);
	pixel->t = MAX_DB;
	pixel->rgb = ft_rgb_mult_db(rt->al.rgb, rt->al.light);
	ft_iter_obj(rt, pixel, (t_lutch){o, d}, &(t_range){0.0001, MAX_DB});
	if (pixel->t == MAX_DB)
	{
        	ref_color = pixel->rgb;
		free(pixel);
		return (ref_color);
	}
	pixel->p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel->t * 0.9999));
	pixel->rgb = ft_compute_lighting(rt, pixel->normal,
			ft_xyz_mult_db(d, -1.0), pixel);
	if (rec <= 0 || pixel->reflective <= 0.01)
	{
        	ref_color = pixel->rgb;
        	free(pixel);
		return (ref_color);
	}
	r = ft_reflect_ray(ft_xyz_mult_db(d, -1.0), pixel->normal);
	ref_color = ft_ray_trace(rt, pixel->p, r, rec - 1);
	ref_color = ft_recurse_color(ref_color, pixel->rgb, pixel->reflective);
	free(pixel);
	return (ref_color);
}
