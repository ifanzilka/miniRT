/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_adds_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:05:02 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 17:06:05 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>

/*
**  Matrix mult vec
**  (new orientir)
**  return vec(xyz)
*/

t_xyz ft_r_u_n_mult_xyz(t_xyz r, t_xyz u,t_xyz n , t_xyz d)
{
    t_xyz res;

    res.x = r.x * d.x + r.y * d.y + r.z * d.z;
    res.y = u.x * d.x + u.y * d.y + u.z * d.z;
    res.z = n.x * d.x + n.y * d.y + n.z * d.z;
    return (res);
}

/*
**  Reflected relative to n ray
**  r - vec
**  n - normal
**  /return 2 * N * dot(N, R) - R;
*/

 t_xyz   ft_reflect_ray(t_xyz r, t_xyz n) 
 {
    t_xyz res;

    res = ft_xyz_mult_db(n,2);
    res = ft_xyz_mult_db(res,ft_xyz_scal(n,r));
    res = ft_xyz_minus(res,r);
    return (res);
}
