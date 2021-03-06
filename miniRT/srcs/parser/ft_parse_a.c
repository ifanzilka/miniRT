/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_A.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:20:25 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 00:36:35 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Ambient lightning
**  identifier: A
**  ambient lighting ratio in range [0.0,1.0]: 0.2
**  R,G,B colors in range [0-255]: 255, 255, 255
**
**  Example:
**  "A 0.2 255,255,255"
*/

/*
**  typedef struct	s_ambient_lightning
**  {
**                  double light;
**                  t_rgb  rgb;
**  }				t_ambient_lightning;
*/

int	ft_parse_a(t_rt *rt, char *str)
{
	int i;

	i = 1;
	(*rt).al.light = ft_atof(str + i);
	if (rt->al.light == 1.0 / 0.0 || rt->al.light > 1.0 || rt->al.light < 0.0)
		ft_error_rt(err_a, rt);
	ft_skip_atof(str, &i);
	(*rt).al.rgb = ft_atoirgb(str, &i);
	if (!(ft_check_rgb((*rt).al.rgb)))
		ft_error_rt(err_a, rt);
	rt->cnt.a += 1;
	return (1);
}
