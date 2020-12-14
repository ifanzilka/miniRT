/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoirgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:39:25 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/14 20:40:36 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

int             ft_check_rgb(t_rgb rgb)
{
    if (rgb.RED < 0 || rgb.RED > 255 || rgb.GREEN < 0 || rgb.GREEN > 255 ||
        rgb.BLUE < 0 || rgb.BLUE > 255 )
        return (0);
    return (1);
}

static  void    ft_init_rgb(t_rgb *rgb)
{
    rgb->RED = -1;
    rgb->GREEN = -1;
    rgb->BLUE = -1;
}

static  int    ft_miss(char *str, int *i)
{
    int cnt;

    cnt = *i;
    while (ft_isspace(str[*i]))
        *i+=1;
    while (str[*i] && (str[*i] == '-' || str[*i] == '+'))
        *i+=1;
    while(ft_isdigit(str[*i]))
        *i+=1;
    if (cnt == *i)
        return(0);
    return (1);    
}

t_rgb           ft_atoirgb(char *str, int *j)
{
    t_rgb rgb;
    int i;

    i = *j;
    ft_init_rgb(&rgb);
    rgb.RED = ft_atoi(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i+=1)))
        return(rgb);
    rgb.GREEN = ft_atoi(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i+=1)))
        return(rgb);
    rgb.BLUE = ft_atoi(str + i);
    if (!(ft_miss(str,&i)))
        ft_init_rgb(&rgb);    
    *j = i;
    return(rgb);
}