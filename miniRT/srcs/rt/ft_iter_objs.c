/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:56:15 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/30 18:56:16 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <ray_tracing.h>

void ft_iter_obj_close(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_pl(rt, pixel, o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_tr(rt,pixel,o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_sq(rt,pixel,o, d,range);
    if (pixel->t != MAX_DB)
        return;
    ft_l_cy(rt,pixel,o, d,range);
}


void ft_iter_obj(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    ft_l_pl(rt, pixel, o, d,range);
    ft_l_tr(rt,pixel,o, d,range);
    ft_l_sq(rt,pixel,o, d,range);
    ft_l_cy(rt,pixel,o, d,range);
}
