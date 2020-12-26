/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_A.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:20:25 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:20:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Ambient lightning
**  identifier: A
**  ambient lighting ratio in range [0.0,1.0]: 0.2
**  R,G,B colors in range [0-255]: 255, 255, 255
**  
**  Example:
**  "A 0.2 255,255,255"   
*/

/*
**  typedef struct	s_ambient_lightning
**  { 
**                  double light;
**                  t_rgb  rgb;
**  }				t_ambient_lightning;
*/

int            ft_parse_A(t_all_obj *my,char *str)
{
    write(1,"FIND A\n",7);
    int i;

    i = 1;
    (*my).al.light = ft_atof(str + i);
    if (my->al.light ==  1.0 / 0.0 || my->al.light > 1.0 || my->al.light < 0.0)
        ft_error(5);
    ft_skip_atof(str, &i);    
    (*my).al.rgb = ft_atoirgb(str, &i);
    if (!(ft_check_rgb((*my).al.rgb)))
        ft_error(5);
    //printf("r:%d\n",my->al.rgb.RED);
    //printf("g:%d\n",my->al.rgb.GREEN);   
    //printf("b:%d\n",my->al.rgb.BLUE);    
    my->cnt.A+=1;    
    return (1);
}