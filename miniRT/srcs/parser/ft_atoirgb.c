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
    if (rgb.red < 0 || rgb.red > 255 || rgb.green < 0 || rgb.green > 255 ||
        rgb.blue < 0 || rgb.blue > 255 )
        return (0);
    return (1);
}

static  void    ft_init_rgb(t_rgb *rgb)
{
    rgb->red = -1;
    rgb->green = -1;
    rgb->blue = -1;
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
    rgb.red = ft_atoi(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i+=1)))
        return(rgb);
    rgb.green = ft_atoi(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i+=1)))
        return(rgb);
    rgb.blue = ft_atoi(str + i);
    if (!(ft_miss(str,&i)))
        ft_init_rgb(&rgb);    
    *j = i;
    return(rgb);
}