/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:59:44 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:39:53 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_skip_atof(char *str, int *j)
{
	int i;

	i = *j;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if ((str[i] && str[i] == '.'))
	{
		i++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	*j = i;
}

static	int	ft_check_an(char *str)
{
	if (*str && !ft_isdigit(*str))
		return (0);
	return (1);
}

static	int	ft_c_an(char *str)
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

double		ft_atof(char *str)
{
	double	res;
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
	if (*str && !ft_isspace(*str) && !ft_isdigit(*str))
		return (res);
	real = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	if (!(*str && *str == '.' && (str++) && ft_check_an(str)))
		return ((double)(sign * real));
	anreal = ft_atoi(str);
	if (ft_c_an(str) == 0)
		return (res);
	res = sign * (real + (anreal / (double)(ft_pow(10, ft_c_an(str)))));
	return (res);
}
