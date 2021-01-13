/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:36:19 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:36:20 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Sphere:
**  identifier: sp
** x,y,z coordinates of the sphere center: 0.0,0.0,20.6
** the sphere diameter: 12.6
** R,G,B colors in range [0-255]: 10, 0, 255
**  Example:
**  "sp 0.0,0.0,20.6 12.6 10,0,255"   
*/

/*
**  typedef struct	s_sphere
**  { 
**                  t_xyz coord_sph_centr;
**                  double diametr;
**                  t_rgb  rgb;
**  }	            t_sphere;
*/

int           ft_parse_sp(t_all_obj *my,char *str)
{
    write(1,"FIND sp\n",8);
    (void) my;
    t_sphere *sp;
    t_list  *newel;
    int i;

    sp = malloc(sizeof(t_sphere));
    i = 2;
    sp->coord_sph_centr = ft_atoi_xyz(str, &i);
    if (!ft_check_xyz(sp->coord_sph_centr))
        ft_error(9);
    sp->diametr = ft_atof(str + i);
    if (sp->diametr == inf || sp->diametr < 0.0)
        ft_error(9);
    sp->diametr = sp->diametr / 2.0;    
    //printf("s1:%s\n",str + i);    
    ft_skip_atof(str,&i);
    //printf("s2:%s\n",str + i);
    sp->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(sp->rgb))
        ft_error(9);
    sp->specular = ft_atoi(str + i);
    printf("speculer : %d\n",sp->specular);    
    newel = ft_lstnew(sp);
    write(1,"TYT\n",4); 
    
    ft_lstadd_back(&my->sphere,newel);
    write(1,"TYT\n",4);
    if (my->sphere == NULL) 
        printf("PZDC2\n");
    //printf("x: %f\n",sp.coord_sph_centr.x);
    //printf("y: %f\n",sp.coord_sph_centr.y);
    //printf("z: %f\n",sp.coord_sph_centr.z);
    //printf("di: %f\n",sp->diametr);
    my->cnt.sp+=1;
    return(1);
}