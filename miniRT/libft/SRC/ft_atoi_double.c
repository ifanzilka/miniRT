/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:22:52 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/11 18:34:59 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	int	ft_cnt_anreal(char *str)
{
	int n;

	n = 0;
	while (*str && ft_isdigit(*str))
	{
		str++;
		n++;
	}
	return (n);
}

double		ft_atoi_double(char *str)
{
	double	res;
	int		cnt;
	int		sign;
	int		real;
	int		anreal;

	sign = 1;
	res = 1.0 / 0.0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	real = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	if (!(*str && *str == '.' && (str++)))
		return (res);
	anreal = ft_atoi(str);
	cnt = ft_cnt_anreal(str);
	if (cnt == 0)
		return (res);
	res = sign * (real + (anreal / (double)(ft_pow(10, cnt))));
	return (res);
}
