/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:26:08 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 17:53:48 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

int				create_rgb(int r, int g, int b);
t_rgb			ft_rgb_mult_db(t_rgb rgb, double a);
t_rgb			ft_rgb_plus_rgb(t_rgb a, t_rgb b);

#endif
