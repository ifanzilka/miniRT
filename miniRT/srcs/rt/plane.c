/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:09:22 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 17:09:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>


void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range *range, t_plane *pl)
{
    double t;
    double dn;
    double on;
    double dd;
 
    dd = -ft_xyz_scal(pl->normal, pl->cord);
    dn = ft_xyz_scal(pl->normal,d);
    on = ft_xyz_scal(pl->normal,o) + dd;
    if (dn == 0)
        return;
    if (fabs(dn) <  0.0000001)
        return;  
    //printf("ku ku\n");
    t = -on / dn;
    if (t < pixel->t  && ft_in_range(range,t))
    {
        //printf("ku ku\n");
        //if (ft_xyz_scal() )
        pixel->t = t;
        pixel->rgb = pl->rgb;
        pixel->normal = pl->normal;
        pixel->specular =pl->specular;//400;
        pixel->reflective = pl->reflective;
        pixel->id = plane;
    }
}

void        ft_l_pl(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list  *l_pl;
    t_plane *pl;

    l_pl = rt->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        ft_intersect_pl(o, d, pixel,range,pl);
        l_pl = l_pl->next;
    }
}

/*
**  ft_l_pl
** rt -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/