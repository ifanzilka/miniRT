/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:16:26 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/27 13:47:36 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H
#include <ray_tracing.h>

typedef	enum
{
	a = 0,
	s = 1,
	d = 2,
	f = 3,
	h = 4,
	g = 5,
	z = 6,
	x = 7,
	c = 8,
	v = 9,
	w = 13,
	plus = 24,
	minus = 27,
	arrow_left = 123,
	arrow_right = 124,
	arrow_down = 125,
	arrow_up = 126,
	rus_x = 30,
	rus_yi = 33,
	n = 45
}	t_key;

void    ft_next_cam(t_vars *vars);
void    ft_prev_cam(t_vars *vars);
void    ft_plus_cam(t_vars *vars);
void    ft_minus_cam(t_vars *vars);
void    ft_right_cam(t_vars *vars);
void    ft_left_cam(t_vars *vars);
void    ft_up_cam(t_vars *vars);
void    ft_down_cam(t_vars *vars);
void    ft_revers_cam(t_vars *vars);
void    ft_plus_al(t_vars *vars);
void    ft_minus_al(t_vars *vars);
void    ft_minus_fov(t_vars *vars);
void    ft_plus_fov(t_vars *vars);
void    ft_norm_cam(t_vars *vars);
#endif
