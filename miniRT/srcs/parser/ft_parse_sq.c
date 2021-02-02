/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:14:07 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 01:44:51 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Square:
**  identifier: sq
** x,y,z coordinates of the square center: 0.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 1.0,0.0,0.0
** side size: 12.6
** R,G,B colors in range [0-255]: 255, 0, 255
**  Example:
**  "sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255"
*/

/*
**  typedef struct	s_square
**  {
**                  t_xyz cord_sq_cen;
**                  t_xyz normal_orientr_vec;
**                  double side;
**                  t_rgb  rgb;
**  }	            t_square;
*/

static void	ft_parse_specular_reflective(t_square *sq, int *i, char *str)
{
	sq->reflective = ft_atof(str + *i);
	ft_skip_atof(str, i);
	sq->specular = ft_atoi(str + *i);
}

int			ft_parse_sq(t_rt *rt, char *str)
{
	t_square	*sq;
	int			i;

	i = 2;
	if (!(sq = malloc(sizeof(t_square))))
		ft_error_rt(err_malloc, rt);
	sq->cord = ft_atoi_xyz(str, &i);
	if (!ft_check_xyz(sq->cord))
		ft_error(11);
	sq->normal = ft_atoi_xyz(str, &i);
	if (!ft_check_normalizate(sq->normal))
		ft_error(11);
	sq->normal = ft_xyz_normalaze(sq->normal);
	sq->side = ft_atof(str + i);
	ft_skip_atof(str, &i);
	if (sq->side == INF)
		ft_error(11);
	sq->rgb = ft_atoirgb(str, &i);
	if (!(ft_check_rgb(sq->rgb)))
		ft_error(11);
	ft_parse_specular_reflective(sq, &i, str);
	if (!(ft_lst_cr_front(&rt->l_sq, sq) && (rt->cnt.sq += 1)))
		ft_error(err_malloc);
	return (1);
}
