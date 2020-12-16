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

int           ft_parse_pl(t_all_obj *my , char *str)
{
    write(1,"FIND pl\n",8);
    (void) str;
    (void) my;
    t_plane *pl;
    int i;
    
    i = 2;
    pl = malloc((sizeof(t_plane)));
    pl->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(pl->cord))
        ft_error(10);
    pl->normal_orientr_vec = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(pl->cord) || !ft_check_normalizate(pl->normal_orientr_vec))
        ft_error(10);
    pl->rgb = ft_atoirgb(str, &i);

    /*printf("x: %f\n",pl->cord.x);
    printf("y: %f\n",pl->cord.y);
    printf("z: %f\n",pl->cord.z);
    printf("x: %f\n",pl->normal_orientr_vec.x);
    printf("y: %f\n",pl->normal_orientr_vec.y);
    printf("z: %f\n",pl->normal_orientr_vec.z);
    printf("r: %d\n",pl->rgb.RED);
    printf("g: %d\n",pl->rgb.GREEN);
    printf("b: %d\n",pl->rgb.BLUE);
    */
    my->cnt.pl+=1;
    return(1);
}
