/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:40:32 by bmarilli          #+#    #+#             */
/*   Updated: 2020/10/31 18:41:36 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Выделяет (с помощью malloc(3)) и возвращает подстроку
** из строки ’s’.
** Подстрока начинается с индекса "start’ и имеет
** максимальный размер "len".
** RETURN
**
** Возвраащет указатель на эту подстроку
** NULL, если выделение не удается.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		len = 0;
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (0);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
