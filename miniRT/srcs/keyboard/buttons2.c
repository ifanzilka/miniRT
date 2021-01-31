/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:24:00 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 17:57:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

void	ft_left_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.x += 0.2;
	dir = ft_xyz_normalaze(dir);
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_up_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.y -= 0.2;
	dir = ft_xyz_normalaze(dir);
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_down_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.y += 0.2;
	dir = ft_xyz_normalaze(dir);
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_revers_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.z *= -1.0;
	dir.x *= -1.0;
	dir.y *= -1.0;
	dir = ft_xyz_normalaze(dir);
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_plus_al(t_vars *vars)
{
	t_rt					*rt;
	t_ambient_lightning		*al;

	rt = vars->rt;
	al = &(rt->al);
	if (al->light + 0.05 < 1.0)
	{
		al->light += 0.05;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}
