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

int            ft_parse_c(t_all_obj *my,char *str)
{
    write(1,"FIND c\n",7);
    t_l_list    *new_cam;
    t_camera     *camera;
    int i;

   
    if (!(camera = malloc(sizeof(t_camera))))
        ft_error(14);    
    i = 1;
    camera->coord_pointer = ft_atoi_xyz(str,&i);
    if (camera->coord_pointer.x == inf1 || camera->coord_pointer.y == inf1
        || camera->coord_pointer.z == inf1)
        ft_error(7);
    camera->camera_direction = ft_atoi_xyz(str,&i);
    if (camera->camera_direction.x == inf1 || camera->camera_direction.y == inf1
        || camera->camera_direction.z == inf1)
        ft_error(7);
    camera->FOV = ft_atof(str + i);
    camera->camera_direction.x *= -1.0;
    camera->camera_direction.y *= -1.0;
    if ((camera->FOV < 0.0) || (camera->FOV) > 180.0)
        ft_error(7);
     if (!(new_cam = ft_l_lsnew(camera)))
        ft_error(14);
    ft_l_lstadd_back(&my->ll_camera,new_cam);   
    //printf("c:%f\n",(*my).camera.normal_orientr_vec.y);
    my->cnt.c+=1;    
    return (1);
}