/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:24:27 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/18 19:24:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rgb.h>

/*
**  Fun create_rgb
**  
**  Example:
** r -> 155  (10011011)
** g -> 240  (11110000)
** b -> 100  (01100100)
** (r << 16) -> (100110110000000000000000) (plus 16 zero bit)
** (g << 8) -> (1111000000000000)
** b ->   (01100100)
** "l" -> oretion OR (bits)
**    (100110110000000000000000)
** or (000000001111000000000000)
**    (000000000000000001100100)
** res(100110111111000001100100)
*/

int		create_rgb( int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int     ft_max3(int a, int b,int c)
{
    int max;
    max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    return (max);        
}

t_rgb   ft_rgb_mult_db(t_rgb rgb, double a)
{
    int max;
    double kf;

    (void) kf;
    rgb.red = (int)((double)rgb.red * a);
    rgb.green = (int)((double)rgb.green * a);
    rgb.blue = (int)((double)rgb.blue * a);

    max = ft_max3(rgb.red,rgb.green,rgb.blue);
    /*
    if (max > 255)
    {   
        kf = 255.0 / (double)max; 
        rgb.red = kf * rgb.red;
        rgb.green = kf * rgb.green;
        rgb.blue = kf * rgb.blue;
    }*/
    if (rgb.red > 255)
        rgb.red = 255;
    if (rgb.green > 255)
        rgb.green = 255;
    if (rgb.blue > 255)
        rgb.blue = 255;
    return (rgb);           
}

t_rgb   ft_rgb_plus_rgb(t_rgb a, t_rgb b)
{
    t_rgb rgb;
    int max;
    double kf;
    rgb.red = a.red + b.red;
    rgb.green = a.green + b.green;
    rgb.blue = a.blue + b.blue;
    max = ft_max3(rgb.red,rgb.green,rgb.blue);
    /*
    if (max > 255)
    {   
        kf = 255.0 / (double)max; 
        rgb.red = kf * rgb.red;
        rgb.green = kf * rgb.green;
        rgb.blue = kf * rgb.blue;
    }*/
    (void) kf;
    if (rgb.red > 255)
        rgb.red = 255;
    if (rgb.green > 255)
        rgb.green = 255;
    if (rgb.blue > 255)
        rgb.blue = 255;
    return (rgb); 
}