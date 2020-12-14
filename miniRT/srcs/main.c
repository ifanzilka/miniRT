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
#include <parse.h>
#include <libft.h>
#include <get_next_line.h>

/*
**  checking the validity of an argument
*/


static int ft_check_argv(int argc, char **argv)
{
	if (argc == 1)
		ft_error(1);
	else if (argc > 2)
		ft_error(2);
	if (ft_strlen(argv[1]) > 3 && ft_strnstr(argv[1] + ft_strlen(argv[1]) - 3,
		".rt",ft_strlen(argv[1])))
		return (1);
	else
		ft_error(3);
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
