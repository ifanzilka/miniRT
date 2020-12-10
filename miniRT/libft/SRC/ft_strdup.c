/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:39:39 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 19:39:14 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Описание:
** Функция strdup() путем обращения к функции malloc() выделяет память,
** достаточную для хранения дубликата строки, на которую указывает str,
** затем производит копирование этой строки в выделенную область и
** возвращает указатель на нее.
*/

static char	*ft_strcpy(char *dst, const char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s1);
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (ft_strcpy(ptr, s1));
}
