/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:14:19 by bmarilli          #+#    #+#             */
/*   Updated: 2020/10/30 02:22:34 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Функция memccpy() копирует байты из строки src в строку dst.
** Если символ "c" (преобразованный в символ без знака)
** встречается в строке src, то копия  останавливается
** и возвращается указатель на байт после копии "c" в строке dst.
** В противном случае копируется n байт
**
** RETURN
**
** Функция memmcpy() возвращает нулевой указатель.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	str1 = (char *)dst;
	str2 = (char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		if ((unsigned char)str1[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
