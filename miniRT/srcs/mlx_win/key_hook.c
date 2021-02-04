/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:03:33 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/05 00:10:12 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <keyboard.h>

static	void	key_hk(int keycode, t_vars *vars)
{
	if (keycode == plus || keycode == 93)
		ft_plus_al(vars);
	else if (keycode == minus || keycode == 91)
		ft_minus_al(vars);
	else if (keycode == rus_x || keycode == 39)
		ft_plus_fov(vars);
	else if (keycode == rus_yi || keycode == 59)
		ft_minus_fov(vars);
	else if (keycode == n || keycode == 110)
		ft_norm_cam(vars);
}

int				key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 65307)
		ft_close_win(vars);
	else if (keycode == arrow_right || keycode == 65363)
		ft_next_cam(vars);
	else if (keycode == arrow_left || keycode == 65361)
		ft_prev_cam(vars);
	else if (keycode == arrow_down || keycode == 65364)
		ft_minus_cam(vars);
	else if (keycode == arrow_up || keycode == 65362)
		ft_plus_cam(vars);
	else if (keycode == d || keycode == 100)
		ft_right_cam(vars);
	else if (keycode == a || keycode == 97) 
		ft_left_cam(vars);
	else if (keycode == w || keycode == 119)
		ft_up_cam(vars);
	else if (keycode == s || keycode == 115)
		ft_down_cam(vars);
	else if (keycode == x || keycode == 120) 
		ft_revers_cam(vars);
	else
		key_hk(keycode, vars);
	return (1);
}
