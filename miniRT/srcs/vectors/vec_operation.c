/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:02:46 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 17:22:40 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>

/*
**  Operation minus  vector xyz
**
**   a - b
**  return -> vector xyz
*/

t_xyz	ft_xyz_minus(t_xyz a, t_xyz b)
{
	t_xyz	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/*
**  Operation plus  vector xyz
**
**   a + b
**  return -> vector xyz
*/

t_xyz	ft_xyz_plus(t_xyz a, t_xyz b)
{
	t_xyz res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/*
**  Operation mult  vector xyz
**
**   a * b
**  return -> vector xyz
*/

t_xyz	ft_xyz_mult_db(t_xyz a, double b)
{
	t_xyz res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return (res);
}

/*
**  Operation div  vector xyz
**
**   a / b
**  return -> vector xyz
*/

t_xyz	ft_xyz_div_db(t_xyz a, double b)
{
	t_xyz	res;

	res.x = a.x / b;
	res.y = a.y / b;
	res.z = a.z / b;
	return (res);
}
