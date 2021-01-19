/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:03:05 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/18 20:03:06 by bmarilli         ###   ########.fr       */
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

t_xyz      ft_create_xyz(double x, double y,double z)
{
    t_xyz o;

    o.x = x;
    o.y = y;
    o.z = z;
    return (o);
}

/*
**  Operation minus  vector xyz
**
**   a - b 
**  return -> vector xyz
*/


t_xyz   ft_xyz_minus(t_xyz a, t_xyz b)
{
    t_xyz res;

    
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

t_xyz   ft_xyz_plus(t_xyz a, t_xyz b)
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

t_xyz   ft_xyz_mult_db(t_xyz a, double b)
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

t_xyz   ft_xyz_div_db(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    return (res);
}

/*
** Len  vector xyz
**
**  return -> Len xyz
*/

double ft_len_vect(t_xyz a)
{
    double len;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (len);
}

/*
**  Operation scalar mult  vector xyz 
**
**   <a , b >
**  return -> vector xyz
*/


double ft_xyz_scal(t_xyz a, t_xyz b)
{
    double res;

    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return (res);
}

t_xyz   ft_xyz_mult_xyz(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z; 
    res.z = a.x *  b.y - a.y * b.x;  
    return(res);
}

t_xyz   ft_xyz_normalaze(t_xyz xyz)
{
    t_xyz res;
    double len;

    len = ft_len_vect(xyz);
    res.x = xyz.x / len;
    res.y = xyz.y / len;
    res.z = xyz.z / len;
    return (res);
}
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