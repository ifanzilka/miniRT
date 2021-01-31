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

int           ft_parse_sp(t_rt *rt,char *str)
{
    t_sphere *sp;
    int i;

    if (!(sp = malloc(sizeof(t_sphere))))
        ft_error_rt(err_malloc,rt);
    i = 2;
    sp->coord_sph_centr = ft_atoi_xyz(str, &i);
    if (!ft_check_xyz(sp->coord_sph_centr))
        ft_error(err_sp);
    sp->diametr = ft_atof(str + i);
    if (sp->diametr == inf || sp->diametr < 0.0)
        ft_error_rt(err_sp,rt);
    sp->diametr = sp->diametr / 2.0;       
    ft_skip_atof(str,&i);
    sp->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(sp->rgb))
        ft_error_rt(err_sp,rt);
    sp->reflective = ft_atof(str + i);
    ft_skip_atof(str,&i);     
    sp->specular = ft_atoi(str + i);
    if (!(ft_lst_cr_front(&rt->l_sphere,sp)))
        ft_error(err_malloc);    
    rt->cnt.sp += 1;
    return(1);
}