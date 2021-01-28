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
    pl.normal = sq->normal;
    pl.cord = sq->cord;
    ft_intersect_pl( o, d, &pixel_loc,range,&pl);
    if (pixel_loc.t == MAX_DB)
        return;  
    t = pixel_loc.t;
    if (t < pixel->t  && ft_in_range(range,t))
    {
        //if ((obj->xyz[0] - (p[0])) <= obj->special/4 && (obj->xyz[1] - (p[1])) <= obj->special/4) //|| (obj->xyz[2] - (p[2])) <= obj->special/2)
        //if ((obj->xyz[0] - (p[0])) >= -obj->special/4 && (obj->xyz[1] - (p[1]))>= -obj->special/4)
        t_xyz p;
        t_range range2;
        range2.min = -sq->side / 4.0;
        range2.max = sq->side / 4.0;
        p = ft_xyz_plus(o, ft_xyz_mult_db(d, t * 0.999));
        if (ft_in_range(&range2,p.x -  sq->cord.x) && ft_in_range(&range2,p.y- sq->cord.y) && ft_in_range(&range2,p.z - sq->cord.z)  )
        {
            pixel->t = t;
            pixel->rgb = sq->rgb;
            pixel->normal = sq->normal;
            pixel->specular = sq->specular;
            pixel->reflective = sq->reflective;
            pixel->id = plane;
        }
    }
}

void    ft_l_sq(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list      *l_sq;
    t_square *sq;

    l_sq = rt->l_sq;
    while (l_sq)
    {
        sq = l_sq->content;
        ft_intersect_ray_square(o,d,pixel,sq, range);
        l_sq = l_sq->next;
    }
}