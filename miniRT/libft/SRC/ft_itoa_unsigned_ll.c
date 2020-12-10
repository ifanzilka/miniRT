/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_ll.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:58:40 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 20:59:44 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_len_str(unsigned long long n)
{
	int	len;

	len = (n <= 0) ? 1 : 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa_unsigned_ll(unsigned long long n)
{
	char				*s;
	int					len;
	unsigned long long	nn;

	nn = n;
	len = ft_cnt_len_str(n);
	if (!(s = (char *)malloc(len + 1)))
		return (NULL);
	s[len] = '\0';
	if (nn == 0)
	{
		s[0] = '0';
	}
	while (nn > 0)
	{
		s[--len] = '0' + nn % 10;
		nn /= 10;
	}
	return (s);
}
