/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:16:25 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 01:17:56 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Triangle:
**  identifier: tr
** x,y,z coordinates of the first point: 10.0,20.0,10.0
** x,y,z coordinates of the second point: 10.0,10.0,20.0
** x,y,z coordinates of the third point: 20.0,10.0,10.0
** R,G,B colors in range [0,255]: 0, 255, 255
**  Example:
**  "tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255"
*/

/*
**  typedef struct	s_triangle
**  {
**                  t_xyz first_point;
**                  t_xyz second_point;
**                  t_xyz third_point;
**                  t_rgb  rgb;
**  }	            t_triang
*/

int	ft_parse_tr(t_rt *rt, char *str)
{
	t_triangle	*tr;
	int			i;

	i = 2;
	tr = malloc(sizeof(t_triangle));
	tr->first = ft_atoi_xyz(str, &i);
	if (!ft_check_xyz(tr->first))
		ft_error(12);
	tr->second = ft_atoi_xyz(str, &i);
	if (!ft_check_xyz(tr->second))
		ft_error(12);
	tr->third = ft_atoi_xyz(str, &i);
	if (!ft_check_xyz(tr->third))
		ft_error(12);
	tr->rgb = ft_atoirgb(str, &i);
	if (!ft_check_rgb(tr->rgb))
		ft_error(12);
	tr->reflective = ft_atof(str + i);
	ft_skip_atof(str, &i);
	tr->specular = ft_atoi(str + i);
	if (!(ft_lst_cr_front(&rt->l_tr, tr)))
		ft_error(err_malloc);
	rt->cnt.tr += 1;
	return (1);
}
