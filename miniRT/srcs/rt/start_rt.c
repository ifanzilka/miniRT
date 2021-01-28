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
#include <keyboard.h>
/*
**  In computer programming, the term hooking covers a range of techniques
** used to alter or augment the behaviour of an operating system,
** of applications, or of other software components by intercepting 
** function calls or messages or events passed between software components.
** Code that handles such intercepted function calls,
** events or messages is called a hook.
*/




/*
** key_hook (function)
**  
** link for window (pointer) mlx
*/

int ft_close_win(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    ft_clear_rt(vars->rt);
    exit(0);
    return (1);
}

int             key_hook(int keycode, t_vars *vars)
{
    printf("Hello from key_hook!%d!\n",keycode);
    if (keycode == 53)
    {
        ft_close_win(vars);
        mlx_destroy_window(vars->mlx, vars->win);
        ft_clear_rt(vars->rt);
        exit(0);
    }
    else if (keycode == arrow_right)
        ft_next_cam(vars);
    else if (keycode == arrow_left)   
        ft_prev_cam(vars);
     else if (keycode == arrow_down)
        ft_minus_cam(vars);     
    else if (keycode == arrow_up)
        ft_plus_cam(vars);
     else if (keycode == d)
        ft_right_cam(vars);
    else if (keycode == a)
        ft_left_cam(vars);
    else if (keycode == w)
        ft_up_cam(vars);
    else if (keycode == s)
        ft_down_cam(vars);
    else if (keycode == x)
        ft_revers_cam(vars);
    else if (keycode == plus)
        ft_plus_al(vars);
    else if (keycode == minus)
        ft_minus_al(vars);
    else if (keycode == rus_x)
        ft_plus_fov(vars);
    else if (keycode == rus_yi)
        ft_minus_fov(vars);
    else if (keycode == n)
        ft_norm_cam(vars);
                                                       
    return(1);
}



void    ft_check_w_h_win(void *mlx_ptr,int x, int y,t_rt *rt)
{
    mlx_get_screen_size(mlx_ptr,&x,&y);
    if (rt->reso.width > x || rt->reso.height > y)
    {
        rt->reso.width = x;
        rt->reso.height = y;
    }
}


int     ft_init_disp(t_rt *rt)
{
    t_vars      *vars;

    vars = NULL;
    if (!(vars = malloc(sizeof(t_vars))) && !(ft_lst_cr_front(&rt->l_p, vars)))
        ft_error_rt(err_malloc,rt);
    if (!(vars->mlx = mlx_init()) && !(ft_lst_cr_front(&(rt->l_p), vars->mlx)))
        ft_error_rt(err_mlx,rt);
    ft_check_w_h_win(vars->mlx,0,0,rt);
    if (!(vars->win = mlx_new_window(vars->mlx, rt->reso.width,
        rt->reso.height, "miniRT")) && !(ft_lst_cr_front(&rt->l_p, vars->win)))
        ft_error_rt(err_mlx,rt);
    vars->rt = rt;    
    mlx_key_hook(vars->win, key_hook, vars);
    mlx_hook(vars->win,17,0L,ft_close_win,vars);  
    //fun trace
    //mlx_pixel_put(vars.mlx,vars.win,10,10,create_rgb(255,255,255));
    cicle_for_pixel(rt,vars);
    mlx_loop(vars->mlx);
    return (1);
}

