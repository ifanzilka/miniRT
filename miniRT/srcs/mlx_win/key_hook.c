/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:03:33 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 21:13:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <keyboard.h>

static	void	key_hk(int keycode, t_vars *vars)
{
	if (keycode == plus)
		ft_plus_al(vars);
	else if (keycode == minus)
		ft_minus_al(vars);
	else if (keycode == rus_x)
		ft_plus_fov(vars);
	else if (keycode == rus_yi)
		ft_minus_fov(vars);
	else if (keycode == n)
		ft_norm_cam(vars);
}

int				key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!%d!\n", keycode);
	if (keycode == 53)
		ft_close_win(vars);
	else if (keycode == arrow_right)
		ft_next_cam(vars);
	else if (keycode == arrow_left)
		ft_prev_cam(vars);
	else if (keycode == arrow_down)
		ft_minus_cam(vars);
	else if (keycode == arrow_up)
		ft_plus_cam(vars);
	else if (keycode == d)
		ft_right_cam(vars);
	else if (keycode == a)
		ft_left_cam(vars);
	else if (keycode == w)
		ft_up_cam(vars);
	else if (keycode == s)
		ft_down_cam(vars);
	else if (keycode == x)
		ft_revers_cam(vars);
	else
		key_hk(keycode, vars);
	return (1);
}
