/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:27:20 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 16:02:02 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

void	ft_next_cam(t_vars *vars)
{
	t_l_list	*ll_cam;
	t_rt		*rt;

	ft_putstr_fd("Next camera!\n", 1);
	rt = vars->rt;
	ll_cam = rt->ll_camera;
	if (ll_cam->next == NULL)
		ft_putstr_fd("Camera in last!\n", 1);
	else
	{
		rt->camera = (t_camera *)ll_cam->next->content;
		rt->ll_camera = rt->ll_camera->next;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}

void	ft_prev_cam(t_vars *vars)
{
	t_l_list	*ll_cam;
	t_rt		*rt;

	ft_putstr_fd("Prev camera!\n", 1);
	rt = vars->rt;
	ll_cam = rt->ll_camera;
	if (ll_cam->prev == NULL)
		ft_putstr_fd("Camera in first!\n", 1);
	else
	{
		rt->camera = (t_camera *)ll_cam->prev->content;
		rt->ll_camera = rt->ll_camera->prev;
		mlx_clear_window(vars->mlx, vars->win);
		cicle_for_pixel(vars->rt, vars);
	}
}

void	ft_plus_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.x *= -1;
	dir.y *= -1;
	cam->cord = ft_xyz_plus(cam->cord, ft_xyz_mult_db(dir, 0.5));
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_minus_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.x *= -1;
	dir.y *= -1;
	cam->cord = ft_xyz_minus(cam->cord, ft_xyz_mult_db(dir, 0.5));
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}

void	ft_right_cam(t_vars *vars)
{
	t_rt		*rt;
	t_camera	*cam;
	t_xyz		dir;

	rt = vars->rt;
	cam = rt->camera;
	dir = cam->direction;
	dir.x -= 0.2;
	dir = ft_xyz_normalaze(dir);
	cam->direction = dir;
	mlx_clear_window(vars->mlx, vars->win);
	cicle_for_pixel(vars->rt, vars);
}
