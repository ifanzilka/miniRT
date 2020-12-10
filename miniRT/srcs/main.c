/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 19:26:13 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/10 19:26:31 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <libft.h>
#include <get_next_line.h>

/*
**  checking the validity of an argument
*/

static int ft_check_argv(int argc, char **argv)
{
	if (argc == 1)
	{
		write(1,"Error\nDon't find .rt file\n",26);
		exit(0);
	}
	else if (argc > 2)
	{
		write(1,"Error\nlots of arguments\n",24);
		exit(0);
	}
	if (ft_strlen(argv[1]) > 3 && ft_strnstr(argv[1] + ft_strlen(argv[1]) - 3,
		".rt",ft_strlen(argv[1])))
		return (1);
	else
	{
		write(1,"Error\nDon't find .rt file\n",26);
		exit(0);
	}
	return (1);
}

int main(int argc, char **argv)
{	

	if (!ft_check_argv(argc, argv) || !ft_parse_rt(argv[1]))
		exit(0);
	while (1)
		;	
	return (1);
}