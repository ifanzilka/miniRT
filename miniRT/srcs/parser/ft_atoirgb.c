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

t_rgb           ft_atoirgb(char *str)
{
    t_rgb rgb;

    rgb.RED = -1;
    rgb.GREEN = -1;
    rgb.BLUE = -1;
    rgb.RED = ft_atoi(str);
    while (ft_isspace(*str))
        str++;
    while (*str && (*str == '-' || *str == '+'))
        str++;
    while(ft_isdigit(*str))
        str++;  
    if (!(*str && (*str == ',') && (str++)))
        return(rgb);
    rgb.GREEN = ft_atoi(str);
    while (ft_isspace(*str))
        str++;
    while (*str && (*str == '-' || *str == '+'))
        str++;
    while(ft_isdigit(*str))
        str++;  
    if (!(*str && (*str == ',') && (str++)))
        return(rgb);
    rgb.BLUE = ft_atoi(str);      
    return(rgb);
}