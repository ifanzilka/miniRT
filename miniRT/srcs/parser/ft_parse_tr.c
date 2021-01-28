/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:16:25 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 23:16:26 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Triangle:
**  identifier: tr
** x,y,z coordinates of the first point: 10.0,20.0,10.0
** x,y,z coordinates of the second point: 10.0,10.0,20.0
** x,y,z coordinates of the third point: 20.0,10.0,10.0
** R,G,B colors in range [0,255]: 0, 255, 255
**  Example:
**  "tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255"   
*/

/*
**  typedef struct	s_triangle
**  { 
**                  t_xyz first_point;
**                  t_xyz second_point;
**                  t_xyz third_point;
**                  t_rgb  rgb;
**  }	            t_triang
*/

int           ft_parse_tr(t_rt *rt , char *str)
{
    write(1,"FIND tr\n",8);
    (void) str;
    (void) rt;
    t_triangle *tr;
    t_list  *newel;
    int i;

    i = 2;
    tr = malloc(sizeof(t_triangle));
    tr->first = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->first))
        ft_error(12);
    tr->second = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->second))
        ft_error(12);
    tr->third= ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->third))
        ft_error(12);
    tr->rgb = ft_atoirgb(str,&i);
    if (!ft_check_rgb(tr->rgb))
        ft_error(12);
    tr->reflective = ft_atof(str + i);
    ft_skip_atof(str,&i);
    printf("reflective : %f\n",tr->reflective);       
    tr->specular = ft_atoi(str + i);
    printf("speculer : %d\n",tr->specular);       
    if (!(newel = ft_lstnew(tr)))
        ft_error(14);    
    ft_lstadd_front(&rt->l_tr,newel); 
    /*printf("r: %d\n",tr->rgb.RED);
    printf("g: %d\n",tr->rgb.GREEN);
    printf("b: %d\n",tr->rgb.BLUE); */
    rt->cnt.tr+=1;
    return (1);
}
