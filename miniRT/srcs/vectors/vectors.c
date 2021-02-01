/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:03:05 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 17:16:33 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>
#include <math.h>

/*
**  Create  vector xyz
**
**  x -> coordinat
**  y -> coordinat
**  z -> coordinat
**  return -> vector xyz
*/

t_xyz	ft_create_xyz(double x, double y, double z)
{
	t_xyz o;

	o.x = x;
	o.y = y;
	o.z = z;
	return (o);
}

/*
** Len  vector xyz
**
**  return -> Len xyz
*/

double	ft_len_vect(t_xyz a)
{
	double	len;

	len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (len);
}

/*
**  Operation scalar mult  vector xyz
**
**   <a , b >
**  return -> vector xyz
*/

double	ft_xyz_scal(t_xyz a, t_xyz b)
{
	double	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return (res);
}

/*
**  Operation  mult  vec a and vec b
**
**   return res (perpendicular a and b)
*/

t_xyz	ft_xyz_mult_xyz(t_xyz a, t_xyz b)
{
	t_xyz	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

/*
**  Operation  normalizate
**
**   return res (vector in len = 1)
*/

t_xyz	ft_xyz_normalaze(t_xyz xyz)
{
	t_xyz	res;
	double	len;

	len = ft_len_vect(xyz);
	res.x = xyz.x / len;
	res.y = xyz.y / len;
	res.z = xyz.z / len;
	return (res);
}
