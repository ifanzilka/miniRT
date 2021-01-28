/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_rt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:18:25 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/27 14:18:27 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_RT_H
# define ERRORS_RT_H

typedef	enum
{
    no_er,
    dont_find,
    lots_arg,
    err_r = 4,
    err_a,
    err_rt,
    err_c,
    err_l,
    err_sp,
    err_cy,
    err_sq,
    err_tr,
    err_mlx,
    err_malloc,
    err_rgb,
    err_pl,
    err_argv
}	t_errors;

void        ft_error(int n);

#endif