/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_n_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:29:16 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 18:29:32 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_n_char(int num, char c, int fd)
{
	int		count;

	count = num;
	while (num-- > 0)
		write(fd, &c, 1);
	return (count);
}
