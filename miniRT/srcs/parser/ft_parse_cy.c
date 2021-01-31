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

static  void          ft_parse_specular_reflective(t_cylinder *cy, int i,char *str)
{
    cy->reflective = ft_atof(str + i);
    ft_skip_atof(str,&i);    
    cy->specular = ft_atoi(str + i);

}

int           ft_parse_cy(t_rt *rt,char *str)
{
    t_cylinder *cy;
    int i;
 
    i = 2;
    if (!(cy = malloc(sizeof(t_cylinder))))
        ft_error_rt(err_malloc,rt);
    cy->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord))
        ft_error_rt(err_cy,rt);
    cy->normal = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord) || !ft_check_normalizate(cy->normal))
        ft_error_rt(err_cy,rt);
    cy->normal = ft_xyz_normalaze(cy->normal); 
    cy->diameter = ft_atof(str + i);
    ft_skip_atof(str, &i);
    cy->height = ft_atof(str +i);
    ft_skip_atof(str, &i);
    if (cy->diameter < 0.0 || cy->height < 0.0)
        ft_error_rt(err_cy,rt);
    cy->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(cy->rgb))
        ft_error_rt(err_cy,rt);
    ft_parse_specular_reflective(cy,i,str);
    if (!(ft_lst_cr_front(&rt->l_cy,cy)))
        ft_error(err_malloc);    
    rt->cnt.cy+=1;
    return (1);
}
