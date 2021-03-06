/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:45:29 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/02 20:24:24 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>

void	ft_error(int n)
{
	if (n == dont_find)
		write(1, "Error\nDon't find .rt file\n", 26);
	else if (n == lots_arg)
		write(1, "Error\nlots of arguments\n", 24);
	else if (n == err_rt)
		write(1, "Don't valid .rt file\n", 21);
	else if (n == err_argv)
		ft_putstr_fd("Argv don't valid\n", 1);
	exit(n);
}

void	ft_error_rt(int n, t_rt *rt)
{
	ft_clear_rt(rt);
	if (n == err_r)
		write(1, "Don't valid R\n", 14);
	else if (n == err_a)
		write(1, "Don't valid A\n", 14);
	else if (n == err_rt)
		write(1, "Don't valid .rt file\n", 21);
	else if (n == err_c)
		write(1, "Don't valid c\n", 14);
	else if (n == err_l)
		write(1, "Don't valid l\n", 14);
	else if (n == err_sp)
		write(1, "Don't valid sp\n", 15);
	else if (n == err_cy)
		write(1, "Don't valid cy\n", 15);
	else if (n == err_sq)
		write(1, "Don't valid sq\n", 15);
	else if (n == err_tr)
		write(1, "Don't valid tr\n", 15);
	else if (n == err_mlx)
		ft_putstr_fd("MLX ERROR\n", 1);
	else if (n == err_malloc)
		ft_putstr_fd("MALLOC ERROR\n", 1);
	else  
		ft_putstr_fd("ERROR\n", 1);	
	exit(n);
}
