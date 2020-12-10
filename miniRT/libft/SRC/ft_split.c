/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:20:15 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 18:27:33 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Описание
** выделяет (с помощью malloc(3)) и возвращает массив
** строк, полученный путем разбиения ’s’ с использованием
** символа ’c’ в качестве разделителя. Массив должен
** заканчиваться нулевым указателем.
**
** RETURN
** Возвращает значение массива новых строк,
** полученного в результате разделения.
** NULL, если выделение не удается.
*/

static size_t	ft_count_words(const char *s, char c)
{
	size_t	cnt;
	char	is_start;

	is_start = 1;
	cnt = 0;
	while (*s)
		if (*(s++) != c)
		{
			if (is_start)
				cnt++;
			is_start = 0;
		}
		else
			is_start = 1;
	return (cnt);
}

static char		*ft_strndup_local(const char *s, size_t len)
{
	size_t	l;
	char	*dup;

	l = ft_strlen(s);
	if (len < l)
		l = len;
	if (!(dup = (char*)malloc(l + 1)))
		return (NULL);
	ft_memcpy(dup, s, l);
	dup[l] = 0;
	return (dup);
}

static char		ft_copy_words(char **arr, const char *s, char c)
{
	char		*word_start;
	size_t		word_i;

	word_start = 0;
	word_i = 0;
	while (*s)
	{
		if (*s != c && !word_start)
			word_start = (char *)s;
		s++;
		if (word_start && (*s == c || *s == '\0'))
		{
			arr[word_i] = ft_strndup_local(word_start, s - word_start);
			if (!arr[word_i++])
			{
				while (--word_i)
					free(arr[word_i]);
				free(arr);
				return (0);
			}
			word_start = 0;
		}
	}
	arr[word_i] = 0;
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char		**arr;

	if (!s)
		return (NULL);
	if (!(arr = malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	if (!ft_copy_words(arr, s, c))
		return (NULL);
	return (arr);
}
