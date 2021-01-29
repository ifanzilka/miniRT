/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:45:29 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/14 18:45:51 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>

void    ft_error(int n)
{
    if (n == 1)
        write(1,"Error\nDon't find .rt file\n",26);
    else if (n == 2)
        write(1,"Error\nlots of arguments\n",24);
	else if (n == 6)
		write(1, "Don't valid .rt file\n", 21);
	else if (n == err_argv)
		ft_putstr_fd("Argv don't valid\n",1);										
    exit(n);
}

void    del_obj(void *p)
{
    //if (p)
        free(p);
	p = NULL;	
}

void    ft_clear_rt(t_rt *rt)
{
    ft_lstclear(&(rt->l_sphere),del_obj);
    ft_lstclear(&(rt->l_light),del_obj);
    ft_lstclear(&(rt->l_pl),del_obj);
    ft_lstclear(&(rt->l_tr),del_obj);
    ft_lstclear(&(rt->l_sq),del_obj);
    ft_lstclear(&(rt->l_cy),del_obj);
	ft_lstclear(&(rt->l_p),del_obj);
	ft_l_lstclear(&(rt->ll_camera),del_obj);
	ft_lstclear(&(rt->l_p),del_obj);
	free(rt);
}

void	ft_error_rt(int n, t_rt *rt)
{
	ft_clear_rt(rt);
 	if (n == 4)
		write(1, "Don't valid R\n", 14);
	else if (n == 5)
		write(1, "Don't valid A\n", 14);
	else if (n == 7)
		write(1, "Don't valid c\n", 14);
	else if (n == 8)
		write(1, "Don't valid l\n", 14);
	else if (n == 9)
		write(1, "Don't valid sp\n", 15);
	else if (n == 10)
		write(1, "Don't valid cy\n", 15);
	else if (n == 11)
		write(1, "Don't valid sq\n", 15);
	else if (n == 12)
		write(1, "Don't valid tr\n", 15);
	else if (n == 13)
		ft_putstr_fd("MLX ERROR\n",1);
	else if (n == 14)
		ft_putstr_fd("MALLOC ERROR\n",1);
	exit (n);
}
