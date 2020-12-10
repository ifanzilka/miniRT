/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_forward.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:40:29 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 20:41:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_add_forward(char **str, char c, int n)
{
	char	*tmp;
	char	*tmp2;

	if (!(tmp = (ft_create_str(c, n))) || !*str)
		return (-1);
	tmp2 = *str;
	if (!(*str = ft_strjoin(tmp, tmp2)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	free(tmp2);
	return (1);
}
