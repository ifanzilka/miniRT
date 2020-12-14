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

t_rgb           ft_atoirgb(char *str, int *i)
{
    t_rgb rgb;

    rgb.RED = -1;
    rgb.GREEN = -1;
    rgb.BLUE = -1;
    rgb.RED = ft_atoi(str + *i);
    while (ft_isspace(str[*i]))
        *i+=1;
    while (str[*i] && (str[*i] == '-' || str[*i] == '+'))
        *i+=1;
    while(ft_isdigit(str[*i]))
        *i+=1;  
    if (!(str[*i] && (str[*i] == ',') && (*i+=1)))
        return(rgb);
    rgb.GREEN = ft_atoi(str + *i);
    while (ft_isspace(str[*i]))
        *i+=1;
    while (str[*i] && (str[*i] == '-' || str[*i] == '+'))
        *i+=1;
    while(ft_isdigit(str[*i]))
        *i+=1;  
    if (!(str[*i] && (str[*i] == ',') && (*i+=1)))
        return(rgb);
    rgb.BLUE = ft_atoi(str + *i);      
    return(rgb);
}