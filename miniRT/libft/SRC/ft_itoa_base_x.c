/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:13:01 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/05 15:46:18 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*res(int i, int n, int *convert, char c)
{
	char		*xbase;
	char		*xxbase;
	char		*base;
	char		*res;

	base = NULL;
	xbase = "0123456789abcdef";
	xxbase = "0123456789ABCDEF";
	if (c == 'x')
		base = xbase;
	else
		base = xxbase;
	res = (char *)malloc(i * sizeof(res));
	i--;
	if (n == 1)
		res[0] = '-';
	while (i >= 0)
	{
		res[n] = base[convert[i]];
		n++;
		i--;
	}
	res[n] = '\0';
	return (res);
}

char			*ft_itoa_base(unsigned long long int value, int base,
		char c)
{
	unsigned long long int	val;
	int						i;
	int						n;
	int						convert[64];

	val = value;
	n = 0;
	i = 0;
	if (val == 0)
		return (ft_strdup("0"));
	while (val != 0)
	{
		convert[i++] = val % base;
		val = val / base;
	}
	return (res(i, n, convert, c));
}
