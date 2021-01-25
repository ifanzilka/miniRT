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

int           ft_parse_tr(t_all_obj *my , char *str)
{
    write(1,"FIND tr\n",8);
    (void) str;
    (void) my;
    t_triangle *tr;
    t_list  *newel;
    int i;

    i = 2;
    tr = malloc(sizeof(t_triangle));
    tr->first_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->first_point))
        ft_error(12);
    tr->second_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->second_point))
        ft_error(12);
    tr->third_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->third_point))
        ft_error(12);
    tr->rgb = ft_atoirgb(str,&i);
    if (!ft_check_rgb(tr->rgb))
        ft_error(12);  
    if (!(newel = ft_lstnew(tr)))
        ft_error(14);    
    ft_lstadd_front(&my->l_tr,newel); 
    /*printf("r: %d\n",tr->rgb.RED);
    printf("g: %d\n",tr->rgb.GREEN);
    printf("b: %d\n",tr->rgb.BLUE); */
    my->cnt.tr+=1;
    return (1);
}
