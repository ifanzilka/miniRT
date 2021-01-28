/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:14:07 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 23:14:17 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Square:
**  identifier: sq
** x,y,z coordinates of the square center: 0.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 1.0,0.0,0.0
** side size: 12.6
** R,G,B colors in range [0-255]: 255, 0, 255
**  Example:
**  "sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255"   
*/

/*
**  typedef struct	s_square
**  { 
**                  t_xyz cord_sq_cen;
**                  t_xyz normal_orientr_vec;
**                  double side;
**                  t_rgb  rgb;
**  }	            t_square;
*/

int           ft_parse_sq(t_rt *rt , char *str)
{
     write(1,"FIND sq\n",8);
    t_square *sq;
    t_list  *newel;
    int i;

    sq = malloc(sizeof(t_square));
    i = 2;
    sq->cord= ft_atoi_xyz(str, &i);
    if (!ft_check_xyz(sq->cord))
        ft_error(11);
    sq->normal = ft_atoi_xyz(str,&i);
    if (!ft_check_normalizate(sq->normal))
        ft_error(11);
    sq->normal = ft_xyz_normalaze(sq->normal);    
    sq->side = ft_atof(str + i);
    ft_skip_atof(str,&i);
    if (sq->side == inf)
        ft_error(11);
   sq->rgb = ft_atoirgb(str,&i);
    if (!(ft_check_rgb(sq->rgb)))
        ft_error(11);
    sq->reflective = ft_atof(str + i);
    ft_skip_atof(str,&i);
    printf("reflective : %f\n",sq->reflective);       
    sq->specular = ft_atoi(str + i);
    printf("speculer : %d\n",sq->specular); 
    if (!(newel = ft_lstnew(sq)))
        ft_error(14);
    ft_lstadd_front(&rt->l_sq,newel); 
    /*
    printf("x: %f\n",sq->cord_sq_cen.x);
    printf("y: %f\n",sq->cord_sq_cen.y);
    printf("z: %f\n",sq->cord_sq_cen.z);
    printf("x: %f\n",sq->normal_orientr_vec.x);
    printf("y: %f\n",sq->normal_orientr_vec.y);
    printf("z: %f\n",sq->normal_orientr_vec.z);
    printf("r: %d\n",sq->rgb.RED);
    printf("g: %d\n",sq->rgb.GREEN);
    printf("b: %d\n",sq->rgb.BLUE);
    printf("side: %f\n",sq->side);
    */
    rt->cnt.sq+=1;
    return(1);
}