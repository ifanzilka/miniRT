/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_with_zero.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:49:12 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 18:49:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_with_zero(int n, int count_zero)
{
	char			*str;
	size_t			max;
	unsigned int	i;

	max = ft_intlen(n) + count_zero + (n < 0 ? 1 : 0);
	if (n < 0)
		i = (unsigned int)(n * (-1));
	else
		i = (unsigned int)(n);
	if (!(str = ft_strnew(max)))
		return (NULL);
	while (i >= 10)
	{
		str[--max] = (i % 10) + 48;
		i /= 10;
	}
	str[--max] = (i % 10) + 48;
	while (count_zero--)
		str[--max] = '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
