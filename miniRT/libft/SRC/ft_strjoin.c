/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:03:27 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 19:18:48 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** выделяет (с помощью malloc(3)) и возвращает новую
** строку, которая является результатом конкатенации
** ’s1’ и ’s2’
**
** RETURN
** Новая строка. NULL, если выделение не удается
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(new_s = (char*)malloc(sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		new_s[i] = *s2;
		s2++;
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
