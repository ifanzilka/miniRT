/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:25:12 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:16:22 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

void	ft_minus_al(t_vars *vars)
{
	t_rt					*rt;
	t_ambient_lightning		*al;

	rt = vars->rt;
	al = &(rt->al);
	if (al->light - 0.05 > 0.0)
	{
		al->light -= 0.05;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
	else
	{
		al->light = 0.0;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}

void	ft_minus_fov(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;

	rt = vars->rt;
	cam = rt->camera;
	if (cam->fov - 10 > 0)
	{
		cam->fov -= 10;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
	else
	{
		cam->fov = 0;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}

void	ft_plus_fov(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;

	rt = vars->rt;
	cam = rt->camera;
	if (cam->fov + 10 < 180)
	{
		cam->fov += 10;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
	else
	{
		cam->fov = 180;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}

void	ft_norm_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.x = 0.0;
	dir.x = 0.0;
	dir.z = 1.0;
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}
