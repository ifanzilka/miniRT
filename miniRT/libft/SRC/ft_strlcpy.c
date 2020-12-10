/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 23:24:21 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 19:30:22 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Функция strlcpy копирует из строки src в буфер dst не более чем size - 1
** символов и гарантированно устанавливает в конец строки нулевой символ
**
** RETURN
**
** strlcpy возвращает размер строки по адресу src
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = 0;
	while (++src_len < size && *src)
		*(dst++) = *(src++);
	if (size)
		*dst = '\0';
	while (*(src++))
		src_len++;
	return (src_len - 1);
}
