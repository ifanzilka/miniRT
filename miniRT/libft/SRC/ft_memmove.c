/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:57:24 by bmarilli          #+#    #+#             */
/*   Updated: 2020/10/30 16:30:36 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Функция memmove() копирует байты count  из строки src в строку dst.
** Эти две строки могут накладываться друг на друга;
** копирование всегда выполняется неразрушающим способом.
** То есть если они в одной области памяти копирование будет
** гарантировано правильным
**
** RETURN
**
** Функция memcpy() возвращает исходное значение dst.
*/

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*new_dest;
	unsigned char		*new_src;
	size_t				i;

	i = 0;
	if (dest == src || len == 0)
		return (dest);
	if (dest < src)
	{
		new_dest = (unsigned char *)dest;
		new_src = (unsigned char *)src;
		while (i < len)
		{
			new_dest[i] = new_src[i];
			i++;
		}
	}
	else
	{
		new_dest = (unsigned char *)dest + (len - 1);
		new_src = (unsigned char *)src + (len - 1);
		while (len--)
			*new_dest-- = *new_src--;
	}
	return (dest);
}
