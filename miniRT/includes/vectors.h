/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:56:18 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/18 19:56:19 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTORS_H
#define VECTORS_H

typedef struct	s_xyz
{
                double x;
                double y;
                double z;
}	            t_xyz;

t_xyz   ft_create_xyz(double x, double y,double z);
t_xyz   ft_xyz_minus(t_xyz a, t_xyz b);
t_xyz   ft_xyz_plus(t_xyz a, t_xyz b);
t_xyz   ft_xyz_mult_db(t_xyz a, double b);
t_xyz   ft_xyz_div_db(t_xyz a, double b);
double  ft_len_vect(t_xyz a);
double  ft_xyz_scal(t_xyz a, t_xyz b);
t_xyz   ft_xyz_mult_xyz(t_xyz a, t_xyz b);

#endif