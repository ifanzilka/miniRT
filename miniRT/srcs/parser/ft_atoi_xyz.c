/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_xyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:55:22 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/03 00:20:25 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>

int					ft_check_xyz(t_xyz xyz_t)
{
	if (xyz_t.x == INF || xyz_t.y == INF || xyz_t.z == INF)
		return (0);
	return (1);
}

static void			ft_miss(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i) += 1;
	while (str[*i] && (str[*i] == '-' || str[*i] == '+'))
		(*i) += 1;
	while (str[*i] && ft_isdigit(str[*i]))
		(*i) += 1;
	if (str[*i] && str[*i] == '.')
	{
		(*i) += 1;
		while (str[*i] && ft_isdigit(str[*i]))
			(*i) += 1;
	}
}

t_xyz				ft_atoi_xyz(char *str, int *j)
{
	t_xyz	xyz;
	int		i;

	i = *j;
	xyz.x = INF;
	xyz.y = INF;
	xyz.z = INF;
	xyz.x = ft_atof(str + i);
	ft_miss(str, &i);
	if (!(str[i] && (str[i] == ',') && (i++)))
		return (xyz);
	xyz.y = ft_atof(str + i);
	ft_miss(str, &i);
	if (!(str[i] && (str[i] == ',') && (i++)))
		return (xyz);
	xyz.z = ft_atof(str + i);
	ft_miss(str, &i);
	*j = i;
	return (xyz);
}
