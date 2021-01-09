/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:49:49 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/26 18:49:50 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "ft_minirt.h"


int     ft_init_disp(t_all_obj *rt);
int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars);
#endif