/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsig_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:55:03 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 18:57:57 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen_base(unsigned long long value, int base)
{
	int i;

	i = 1;
	while (value /= base)
		i++;
	return (i);
}

static char		print_nbr(int value, int reg)
{
	char *str;
	char c;

	if (reg)
		str = ft_strdup("0123456789ABCDEF");
	else
		str = ft_strdup("0123456789abcdef");
	c = str[value];
	ft_strdel(&str);
	return (c);
}

char			*ft_itoa_unsig_base(unsigned long long value, int base,
		int num, int reg)
{
	char		*str;
	int			count;

	count = ft_intlen_base(value, base) + (num > 0 ? num : 0);
	str = malloc(sizeof(char) * (count + 1));
	str[count] = '\0';
	while (value >= (unsigned long long)base)
	{
		str[--count] = print_nbr(value % base, reg);
		value /= base;
	}
	str[--count] = print_nbr(value % base, reg);
	while (num-- > 0)
		str[--count] = print_nbr(0, reg);
	return (str);
}
