/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_xyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:55:22 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/14 20:55:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

//#define inf 1.0 / 0.0

int                    ft_check_xyz(t_xyz xyz_t)
{
    if (xyz_t.x == inf || xyz_t.y == inf || xyz_t.z == inf)
        return (0);
    return (1);
}

static void           ft_miss(char *str, int *i)
{
    while (str[*i] && ft_isspace(str[*i]))
        (*i) +=1;
    while (str[*i] && (str[*i] == '-' || str[*i] == '+'))
        (*i)+=1;    
    while (str[*i] && ft_isdigit(str[*i]))
        (*i)+= 1;
    if (str[*i] && str[*i] == '.')
    {
        (*i)+=1;
        while (str[*i] && ft_isdigit(str[*i]))
            (*i)+=1;
    }
}

t_xyz          ft_atoi_xyz(char *str, int *j)
{
    t_xyz xyz;
    int i;

    i = *j;
    xyz.x = 1.0 / 0;
    xyz.y = 1.0 / 0;
    xyz.z = 1.0 / 0;
    xyz.x = ft_atof(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i++)))
        return(xyz);
    xyz.y = ft_atof(str + i);
    ft_miss(str,&i);
    if (!(str[i] && (str[i] == ',') && (i++)))
        return(xyz);
    xyz.z = ft_atof(str + i);
    ft_miss(str,&i);
    *j = i;
    return(xyz);
}
