/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/15 11:16:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>
#include <bmp.h>

# ifndef depth
#define depth 0
#endif



/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/



int     cicle_for_pixel(t_rt *rt,t_vars *vars)
{
    int cx;
    int cy;
    t_rgb rgb;
    t_xyz d;

    cx = 0;
    cy = 0;
    while (cy < rt->reso.height)
    {
        while(cx < rt->reso.width)
        {    
            d = ft_init_d(&cx,&cy,rt);
            rgb = ft_ray_trace(rt, rt->camera->cord, d ,(t_range){0.0001,MAX_DB},depth);
            my_mlx_pixel_put(&(vars->img),cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            ft_percent_render(cx,cy,rt->reso.width,rt->reso.height);
            cx++;
        }
        cx = 0;
        cy++;
    }
    if (vars->bmp)
        ft_create_bmp(rt,&(vars->img));
    else    
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0); 
    return (1);
}
