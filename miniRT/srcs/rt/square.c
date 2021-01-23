/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:42:27 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 17:42:32 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>


void     ft_intersect_ray_square(t_xyz o,t_xyz d,t_pixel *pixel,t_square *sq, t_range *range)
{   
    t_pixel pixel_loc;
    t_plane pl;
    double t;

    pixel_loc.t =  MAX_DB;
    pl.normal_orientr_vec = sq->normal_orientr_vec;
    pl.cord = sq->cord_sq_cen;
    ft_intersect_pl( o, d, &pixel_loc,range,&pl);

    if (pixel_loc.t == MAX_DB)
        return;  
    t = pixel_loc.t;
    if (t < pixel->t  && ft_in_range(range,t))
    {
        t_xyz p;
        t_range range2;
        range2.min = -sq->side / 2.0;
        range2.max = sq->side / 2.0;
        p = ft_xyz_plus(o, ft_xyz_mult_db(d, t * 0.999));
        if (ft_in_range(&range2,p.x -  sq->cord_sq_cen.x) && ft_in_range(&range2,p.y- sq->cord_sq_cen.y) && ft_in_range(&range2,p.z - sq->cord_sq_cen.z)  )
        {
            
            pixel->t = t;
            pixel->rgb = sq->rgb;
            pixel->normal = sq->normal_orientr_vec;
            pixel->specular = 0;//400;
            pixel->reflective = 0;
            pixel->id = plane;
        }
    }
}

void    ft_l_sq(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list      *l_sq;
    t_square *sq;

    l_sq = all_obj->l_sq;
    while (l_sq)
    {
        sq = l_sq->content;
        ft_intersect_ray_square(o,d,pixel,sq, range);
        l_sq = l_sq->next;
    }
}