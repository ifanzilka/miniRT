/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:36:14 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 20:37:54 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_create_str(char c, int n)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 0)
		return (NULL);
	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = 0;
	return (str);
}
