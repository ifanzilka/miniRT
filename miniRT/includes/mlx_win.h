/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:53:41 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/30 17:53:42 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MLX_WIN_H
#define MLX_WIN_H

#include <ft_minirt.h>

/*
**
**  s_vars 
**  mlx -> pointer libary
**  win -> link for window 
*/

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct  s_vars 
{
    t_img       img;
    void        *mlx;
    void        *win;
    void        *rt;
    int         bmp;
}                t_vars;

int     ft_init_disp(t_rt *rt);
int     ft_init_img(t_rt *rt);
int     ft_close_win(t_vars *vars);
int     key_hook(int keycode, t_vars *vars);
void    ft_check_w_h_win(void *mlx_ptr,int x, int y,t_rt *rt);
void    my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif