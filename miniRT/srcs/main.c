/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 19:26:13 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 15:20:56 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

/*
**  checking the validity of an argument
*/

static int	ft_check_argv(int argc, char **argv)
{
	if (argc == 1)
		ft_error(dont_find);
	else if (argc > 3)
		ft_error(lots_arg);
	if (ft_strlen(argv[1]) > 3 && ft_strnstr(argv[1] + ft_strlen(argv[1])
		- 3, ".rt", ft_strlen(argv[1])))
	{
		if (argc == 2)
			return (1);
		else if (ft_strlen(argv[2]) == 6 && !ft_strncmp(argv[2],
			"--save", 6))
			return (1);
		else
			ft_error(err_argv);
	}
	else
		ft_error(dont_find);
	return (0);
}

int			main(int argc, char **argv)
{
	if (!ft_check_argv(argc, argv) || !ft_parse_rt(argv[1], argc))
		exit(0);
	return (1);
}
