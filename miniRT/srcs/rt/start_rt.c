/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:24:42 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/26 18:24:47 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include <mlx.h>

void    ft_check_w_h_win(void *mlx_ptr,int x, int y,t_all_obj *rt)
{
    (void) rt;

    mlx_get_screen_size(mlx_ptr,&x,&y);
    if (rt->reso.width > x || rt->reso.height > y)
    {
        rt->reso.width = x;
        rt->reso.height = y;
    }

    printf("x: %d",x);
    printf("y: %d",y);
}

int     ft_init_disp(t_all_obj *rt)
{
    void    *mlx_ptr;
    void    *mlx_win;
    if (!(mlx_ptr = mlx_init()))
        ft_error(13);
    ft_check_w_h_win(mlx_ptr,0,0,rt);
    mlx_win = mlx_new_window(mlx_ptr, rt->reso.width, rt->reso.height,
        "miniRT");
    mlx_loop(mlx_ptr);

    return (1);
}

