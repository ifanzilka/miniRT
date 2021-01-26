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

int           ft_parse_l(t_all_obj *my,char *str)
{
    write(1,"FIND l\n",7);
    t_light *light;
    t_list  *newel;
    int i;

    light = malloc(sizeof(t_light));
    i = 1;
    light->cord_l_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(light->cord_l_point))
        ft_error(8);
    light->light_brightness = ft_atof(str + i);
    if (light->light_brightness > 1.0 || light->light_brightness < 0.0)
        ft_error(8);
    ft_skip_atof(str,&i);
    light->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(light->rgb))
        ft_error(8);
    newel = ft_lstnew(light);
    if (!newel)
        write(1,"CRASH\n",6);
    t_light *a;
    a = newel->content;    
    //printf(newel->content)    
    write(1,"TY!\n",4);
    ft_lstadd_front(&my->l_light,newel);
    write(1,"TYT\n",4);
    if (my->l_light == NULL)
        printf("PZDC\n");       
    /*printf("s:%s\n",str + i);    
    printf("x:%f\n",(*my).light.cord_l_point.x);
    printf("y:%f\n",(*my).light.cord_l_point.y);
    printf("z:%f\n",(*my).light.cord_l_point.z);
    printf("lb:%f\n",(*my).light.light_brightness);
    printf("r:%d\n",(*my).light.rgb.RED);
    printf("g:%d\n",(*my).light.rgb.GREEN);
    printf("b:%d\n",(*my).light.rgb.BLUE);*/
    my->cnt.l+=1;
    return (1);
}
