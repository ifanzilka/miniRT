/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 14:05:26 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>
#include <bmp.h>
#ifndef DEPTH
# define DEPTH 3
#endif

/*
**  Cicle for all pixel
**
** Example:
** 600 600
*/

static void	ft_trace_rgb(t_vars *vars, int cx, int cy, t_xyz *d)
{
	t_rgb	rgb;
	t_rt	*rt;

	rt = vars->rt;
	rgb = ft_ray_trace(rt, rt->camera->cord, *d, DEPTH);
	my_mlx_pixel_put(&(vars->img), cx, cy,
	create_rgb(rgb.red, rgb.green, rgb.blue));
}

int			cicle_for_pixel(t_rt *rt, t_vars *vars)
{
	int		cx;
	int		cy;
	t_xyz	d;

	cx = 0;
	cy = 0;
	while (cy < rt->reso.height)
	{
		while (cx < rt->reso.width)
		{
			d = ft_init_d(&cx, &cy, rt);
			ft_trace_rgb(vars, cx, cy, &d);
			ft_percent_render(cx, cy, rt->reso.width, rt->reso.height);
			cx++;
		}
		cx = 0;
		cy++;
	}
	if (vars->bmp)
		ft_create_bmp(rt, &(vars->img));
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (1);
}
