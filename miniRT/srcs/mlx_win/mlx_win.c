/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:51:52 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 20:49:59 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_win.h>
#include <ft_minirt.h>
#include <ray_tracing.h>
#include "mlx.h"
#include <keyboard.h>

/*
**  In computer programming, the term hooking covers a range of techniques
** used to alter or augment the behaviour of an operating system,
** of applications, or of other software components by intercepting
** function calls or messages or events passed between software components.
** Code that handles such intercepted function calls,
** events or messages is called a hook.
*/

int		ft_close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	ft_clear_rt(vars->rt);
	exit(0);
	return (1);
}

/*
** key_hook (function)
**
** link for window (pointer) mlx
*/

void	ft_check_w_h_win(void *mlx_ptr, int x, int y, t_rt *rt)
{
	mlx_get_screen_size(mlx_ptr, &x, &y);
	if (rt->reso.width > x || rt->reso.height > y)
	{
		rt->reso.width = x;
		rt->reso.height = y;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
