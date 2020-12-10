/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:24:28 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 22:40:40 by bmarilli         ###   ########.fr       */
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
** Выделяет (с помощью malloc(3)) и возвращает копию
** ’s1’ с символами, указанными в ’set’, удаленными
** из начала и конца строк
**
** RETURN
**
** Обрезанная строка. NULL, если выделение не удается.
*/

/*
** OLD
**
**	int		ft_isset(char c, const char *set)
**	{
**		while (*set)
**		{
**			if (*set == c)
**				return (1);
**			set++;
**		}
**		return (0);
**	}
**
**	int		ft_len_set(char const *s1, char const *set)
**	{
**		int	len;
**		int	cnt;
**		int	i;
**
**		i = 0;
**		cnt = 0;
**		len = ft_strlen(s1);
**		while (s1[i] && ft_isset(s1[i], set))
**		{
**			i++;
**			cnt++;
**		}
**		if (cnt == len)
**			return (0);
**		i = len - 1;
**		while (s1[i] && ft_isset(s1[i], set))
**		{
**			cnt++;
**			i--;
**		}
**		return (len - cnt);
**	}
**
**	char	*ft_strtrim(char const *s1, char const *set)
**	{
**		char	*ptr;
**		int		i;
**		int		len;
**		int		j;
**
**		if (!set || !s1)
**			return (0);
**		j = 0;
**		len = ft_len_set(s1, set);
**		i = 0;
**		if (!(ptr = (char *)ft_calloc(len + 1, sizeof(char))))
**			return (0);
**		while (ft_isset(s1[i], set))
**			i++;
**		while (j < len)
**		{
**			ptr[j] = s1[i];
**			j++;
**			i++;
**		}
**		ptr[j] = 0;
**		return (ptr);
**	}
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	res = ft_substr(s1, 0, i + 1);
	return (res);
}
