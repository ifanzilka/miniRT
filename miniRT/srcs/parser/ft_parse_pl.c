/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:43:41 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:43:42 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Plane:
**  identifier: pl
** x,y,z coordinates: 0.0,0.0,-10.0
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 0.0,0.0,1.0
** R,G,B colors in range [0-255]: 0, 0, 255
**  Example:
**  "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"   
*/

/*
**  typedef struct	s_plane
**  { 
**                  t_xyz cord;
**                  t_xyz normal_orientr_vec;
**                  t_rgb  rgb;
**  }	            t_plane;
*/

int           ft_parse_pl(t_rt *rt , char *str)
{
    t_plane *pl;
    int i;
    
    i = 2;
    if (!(pl = malloc((sizeof(t_plane)))))
        ft_error_rt(err_malloc,rt);
    pl->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(pl->cord))
        ft_error_rt(err_pl,rt);
    pl->normal = ft_atoi_xyz(str,&i);
    pl->normal = ft_xyz_normalaze(pl->normal);
    if (!ft_check_xyz(pl->cord) || !ft_check_normalizate(pl->normal))
        ft_error_rt(err_pl,rt);
    pl->rgb = ft_atoirgb(str, &i);
    pl->reflective = ft_atof(str + i);
    ft_skip_atof(str,&i); 
    pl->specular = ft_atoi(str + i);
    if (!(ft_lst_cr_front(&rt->l_pl,pl)))
        ft_error(err_malloc);       
    rt->cnt.pl+=1;
    return(1);
}
