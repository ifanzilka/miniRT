/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:25:55 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:25:56 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

#define inf1 1.0 / 0.0
/*
**  Camera
**  identifier: c
** x,y,z coordinates of the view point: 0.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
** 0.0,0.0,1.0
** FOV : Horizontal field of view in degrees in range [0,180]
**  Example:
**  "c -50.0,0,20 0,0,1 70"   
*/

/*
**  typedef struct	s_camera
**  { 
**                  t_xyz coord_pointer;
**                  t_xyz normal_orientr_vec;
**                  double FOV;
**  }	            t_camera;
*/

int            ft_parse_c(t_rt *rt,char *str)
{
    t_camera    *camera;
    int i;

    if (!(camera = malloc(sizeof(t_camera))))
        ft_error(err_malloc);    
    i = 1;
    camera->cord = ft_atoi_xyz(str,&i);
    if (camera->cord.x == inf1 || camera->cord.y == inf1
        || camera->cord.z == inf1)
        ft_error_rt(err_c,rt);
    camera->direction = ft_atoi_xyz(str,&i);
    if (camera->direction.x == inf1 || camera->direction.y == inf1
        || camera->direction.z == inf1)
        ft_error_rt(err_c,rt);
    camera->fov = ft_atof(str + i);
    // camera->direction.x *= -1.0;
    // camera->direction.y *= -1.0;
    if ((camera->fov < 0.0) || (camera->fov) > 180.0)
        ft_error_rt(err_c,rt);
     if (!(ft_l_lst_cr_front(&(rt->ll_camera),camera)))
        ft_error_rt(err_malloc,rt);   
    rt->cnt.c+=1;    
    return (1);
}