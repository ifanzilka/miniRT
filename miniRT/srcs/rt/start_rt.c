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
#include "mlx.h"

typedef struct  s_vars 
{
    void        *mlx;
    void        *win;
}                t_vars;

int             key_hook(int keycode, t_vars *vars)
{
    (void) vars;
    printf("Hello from key_hook!%d!\n",keycode);
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        //clear struct
        exit(0);
    }
    return(1);
}

int ft_close_win(t_vars *vars)
{
   (void) vars;

    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (1);
}

void    ft_check_w_h_win(void *mlx_ptr,int x, int y,t_all_obj *rt)
{
    (void) rt;

    mlx_get_screen_size(mlx_ptr,&x,&y);
    if (rt->reso.width > x || rt->reso.height > y)
    {
        rt->reso.width = x;
        rt->reso.height = y;
    }
}

int     ft_init_disp(t_all_obj *rt)
{
    t_vars      vars;

    if (!(vars.mlx = mlx_init()))
        ft_error(13);
    ft_check_w_h_win(vars.mlx,0,0,rt);
    vars.win = mlx_new_window(vars.mlx, rt->reso.width, rt->reso.height,
        "miniRT");
    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win,17,0L,ft_close_win,&vars);    
    mlx_loop(vars.mlx);

    return (1);
}

