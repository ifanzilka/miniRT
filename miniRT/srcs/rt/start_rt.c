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

#include <mlx_win.h>
#include <ft_minirt.h>
#include <ray_tracing.h>
#include "mlx.h"

int     ft_init_img(t_rt *rt)
{
    t_vars      *vars;
    t_img       *img;

    vars = NULL;
    if (!(vars = malloc(sizeof(t_vars))) || !(ft_lst_cr_front(&rt->l_p, vars)))
        ft_error_rt(err_malloc,rt);
    if (!(vars->mlx = mlx_init()) || !(ft_lst_cr_front(&(rt->l_p), vars->mlx)))
        ft_error_rt(err_mlx,rt);
    img = &(vars->img);
    ft_check_w_h_win(vars->mlx,0,0,rt);
    img->img = mlx_new_image(vars->mlx, rt->reso.width, rt->reso.height);
    img->addr =mlx_get_data_addr(img->img, &(img->bits_per_pixel),
        &(img->line_length),&(img->endian));
    vars->rt = rt;
    vars->bmp = 1;
    write(1,"Start Rendering...\n",19);
    cicle_for_pixel(rt,vars);
    ft_putstr_fd("Screen create !\n",1);
    return(1);
}

int     ft_init_disp(t_rt *rt)
{
    t_vars      *vars;
    t_img       *img;

    vars = NULL;
    if (!(vars = malloc(sizeof(t_vars))) || !(ft_lst_cr_front(&rt->l_p, vars)))
        ft_error_rt(err_malloc,rt);
    if (!(vars->mlx = mlx_init()) || !(ft_lst_cr_front(&(rt->l_p), vars->mlx)))
        ft_error_rt(err_mlx,rt);
    img = &(vars->img);      
    ft_check_w_h_win(vars->mlx,0,0,rt);
    img->img = mlx_new_image(vars->mlx, rt->reso.width, rt->reso.height);
    img->addr =mlx_get_data_addr(img->img, &(img->bits_per_pixel), 
        &(img->line_length),&(img->endian));
    if (!(vars->win = mlx_new_window(vars->mlx, rt->reso.width,
        rt->reso.height, "miniRT")) && !(ft_lst_cr_front(&rt->l_p, vars->win)))
        ft_error_rt(err_mlx,rt);    
    vars->rt = rt;
    vars->bmp = 0;    
    mlx_key_hook(vars->win, key_hook, vars);
    mlx_hook(vars->win,17,0L,ft_close_win,vars);
    write(1,"Start Rendering...\n",19);  
    cicle_for_pixel(rt,vars);
    mlx_loop(vars->mlx);
    return (1);
}

