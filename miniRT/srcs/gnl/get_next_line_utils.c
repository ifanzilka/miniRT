/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:10:47 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/10 14:32:55 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

char		*ft_strchr(const char *s, int c)
{
	int		i;
	int		n;

	n = (int)ft_strlen(s);
	i = 0;
	while (i <= n)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
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
