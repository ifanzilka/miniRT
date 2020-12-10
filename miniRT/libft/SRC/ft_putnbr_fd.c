/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:09:18 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/02 12:51:35 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Выводит целое число ’n’ в заданный
** дескриптор
*/

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	num = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -1;
	}
	num = num * (unsigned)(n);
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}
