/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:39:48 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:39:50 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Cylinder:
**  identifier: cy
** x,y,z coordinates: 50.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 0.0,0.0,1.0
** the cylinder diameter: 14.2
** the cylinder height: 21.42
** R,G,B colors in range [0,255]: 10, 0, 255
**  Example:
**  "cy 50.0,0.0,20.6 0.0,0.0,1.0  14.2 21.42 10,0,255"   
*/

/*
**  typedef struct	s_cylinder
**  { 
**                  t_xyz cord;
**                  t_xyz normal_orientr_vec;
**                  double diameter;
**                  double height;
**                  t_rgb  rgb;
**  }	            t_cylinder;
*/

int           ft_parse_cy(t_all_obj *my,char *str)
{
    (void) my;
    (void) str;
    int i;
    write(1,"FIND cy\n",8);
    t_cylinder *cy;
    t_list  *newel;
    i = 2;
    cy = malloc(sizeof(t_cylinder));
    cy->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord))
        ft_error(10);
    cy->normal_orientr_vec = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord) || !ft_check_normalizate(cy->normal_orientr_vec))
        ft_error(10);
     cy->normal_orientr_vec = ft_xyz_normalaze(cy->normal_orientr_vec); 
    cy->diameter = ft_atof(str + i);
    ft_skip_atof(str, &i);
    cy->height = ft_atof(str +i);
    ft_skip_atof(str, &i);
    if (cy->diameter < 0.0 || cy->height < 0.0)
        ft_error(10);
   cy->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(cy->rgb))
        ft_error(10);
    if (!(newel = ft_lstnew(cy)))
        ft_error(14);
    ft_lstadd_front(&my->l_cy,newel);     

    /*
    printf("x: %f\n",cy->cord.x);
    printf("y: %f\n",cy->cord.y);
    printf("z: %f\n",cy->cord.z);
    printf("x: %f\n",cy->normal_orientr_vec.x);
    printf("y: %f\n",cy->normal_orientr_vec.y);
    printf("z: %f\n",cy->normal_orientr_vec.z);
    printf("r: %d\n",cy->rgb.RED);
    printf("g: %d\n",cy->rgb.GREEN);
    printf("b: %d\n",cy->rgb.BLUE);
    printf("d: %f\n",cy->diameter);
    printf("h: %f\n",cy->height);
    */
    my->cnt.cy+=1;
    return (1);
}
