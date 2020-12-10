/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:36:07 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/26 18:36:43 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*s;

	if (size == 0 || (s = (char *)malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	ft_bzero((void *)s, size);
	return ((void *)s);
}
