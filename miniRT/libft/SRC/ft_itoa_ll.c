/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:51:56 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 20:52:58 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_len_str(long long int n)
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

char		*ft_itoa_ll(long long int n)
{
	char			*s;
	int				len;
	long long int	nn;

	nn = n;
	len = ft_cnt_len_str(n);
	if (!(s = (char *)malloc(len + 1)))
		return (NULL);
	s[len] = '\0';
	if (nn < 0)
	{
		s[0] = '-';
		nn = -nn;
	}
	else if (nn == 0)
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
