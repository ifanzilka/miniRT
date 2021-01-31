/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:58:13 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/30 18:58:16 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray_tracing.h>

void    ft_percent_render(int x, int y, int width, int height)
{
    int perc;
    char *str;
    size_t i;

    i = 0;
    perc = ((double)(x + y * width) / (double)(height * width) * 100);
    str = ft_itoa(perc);
    if (!str)
        return;
    write(1,str,ft_strlen(str));
    write(1,"%",1);    
    write(1,"\b",1);
    while (i++ < ft_strlen(str))
        write(1,"\b",1);
    free(str);
}