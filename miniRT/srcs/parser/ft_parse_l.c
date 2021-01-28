/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:32:27 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:32:29 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Light
**  identifier: l
** x,y,z coordinates of the light point: 0.0,0.0,20.6
** the light brightness ratio in range [0.0,1.0]: 0.6
** R,G,B colors in range [0-255]: 10, 0, 255
**  Example:
**  "l -40.0,50.0,0.0 0.6 10,0,255"   
*/

/*
**  typedef struct	s_light
**  { 
**                  t_xyz cord_l_point;
**                  double light_brightness;
**                  t_rgb  rgb;
**  }	            t_light;
*/

int           ft_parse_l(t_rt *rt,char *str)
{
    write(1,"FIND l\n",7);
    t_light *light;
    t_list  *newel;
    int i;

    if (!(light = malloc(sizeof(t_light))))
        ft_error(err_malloc);
    i = 1;
    light->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(light->cord))
        ft_error(err_l);
    light->intensive = ft_atof(str + i);
    if (light->intensive > 1.0 || light->intensive < 0.0)
        ft_error(err_l);
    ft_skip_atof(str,&i);
    light->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(light->rgb))
        ft_error(err_l);
    newel = ft_lstnew(light);
    if (!newel)
        write(1,"CRASH\n",6);
    t_light *a;
    a = newel->content;    
    //printf(newel->content)    
    write(1,"TY!\n",4);
    ft_lstadd_front(&rt->l_light,newel);
    write(1,"TYT\n",4);
    if (rt->l_light == NULL)
        printf("PZDC\n");       
    /*printf("s:%s\n",str + i);    
    printf("x:%f\n",(*rt).light.cord_l_point.x);
    printf("y:%f\n",(*rt).light.cord_l_point.y);
    printf("z:%f\n",(*rt).light.cord_l_point.z);
    printf("lb:%f\n",(*rt).light.light_brightness);
    printf("r:%d\n",(*rt).light.rgb.RED);
    printf("g:%d\n",(*rt).light.rgb.GREEN);
    printf("b:%d\n",(*rt).light.rgb.BLUE);*/
    rt->cnt.l+=1;
    return (1);
}
