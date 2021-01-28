/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_R.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:17:19 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/16 22:17:22 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  Resolution
**  identifier: R
**  x render size
**  y render size
**  
**  Example:
**  "R 1920 1080"   
*/


/*
**  typedef struct	s_resolution
**  {
**                    int width;
**                    int height;
**  }			    t_resolution;
*/

int            ft_parse_R(t_rt *rt,char *str)
{
    int width;
    int height;

    if ((*rt).cnt.R > 1)
         ft_error(err_r);
    width = -1;
    height = -1;
    write(1,"FIND R\n",7);
    str++;
    width = ft_atoi(str);
    while (*str && (ft_isspace(*str)))
        str++;    
    while (*str && ft_isdigit(*str))
        str++;
    height = ft_atoi(str);
    rt->reso.width = width;
    rt->reso.height = height;
    rt->cnt.R += 1;
    if (width <= 0 || height <= 0)
        ft_error(err_r);
    return (1);
}