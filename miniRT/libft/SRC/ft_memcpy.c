/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:14:54 by bmarilli          #+#    #+#             */
/*   Updated: 2020/10/30 16:48:19 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Функция memcpy() копирует n байт из области памяти src в область памяти dst.
** Если dst и src перекрываются, поведение не определено.
**
** RETURN
**
** Функция memcpy() возвращает исходное значение dst.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	if (!dst && !src)
		return (0);
	str1 = dst;
	str2 = (char *)src;
	i = 0;
	while (i < n)
	{
		*(str1 + i) = *(str2 + i);
		i++;
	}
	return (dst);
}
