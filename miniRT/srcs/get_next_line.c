/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:38:02 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/08 06:51:49 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define BUFFER_SIZE 1000
/*
** # 1 parameter: file descriptor to read
** # 2. parameter: Value of what was read
** Return value
** 1: the string was read
** 0 : EOF has been reached
** -1: an error occurred
*/

static int		ft_find_zero(char **last, char **line)
{
	if (ft_strchr(*last, '\0'))
	{
		*line = ft_strdup(*last);
		free(*last);
		*last = NULL;
	}
	return (0);
}

static int		ft_nbytes_error(ssize_t *nbytes, char **last)
{
	if (*nbytes < 0)
	{
		if (*last != NULL)
		{
			free(*last);
			*last = NULL;
		}
		return (1);
	}
	return (0);
}

static int		ft_reads_end(ssize_t nbytes, char **last, char **line)
{
	char	*tmp;
	char	*tmp2;

	if (!nbytes && !*last)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ft_nbytes_error(&nbytes, &*last))
		return (-1);
	if ((tmp = ft_strchr(*last, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*last);
		tmp2 = ft_strdup(tmp + 1);
		if (!*line || !tmp2)
			return (-1);
		free(*last);
		*last = tmp2;
		return (1);
	}
	ft_find_zero(&*last, &*line);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char			*buf;
	ssize_t			nbytes;
	char			*tmp;
	static	char	*last[1025];

	if (!line || fd < 0 || fd > 1025 || BUFFER_SIZE <= 0 ||
		!(buf = (char *)malloc(BUFFER_SIZE + 1)) || (read(fd, buf, 0) < 0))
		return (-1);
	while ((nbytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[nbytes] = '\0';
		if (!last[fd])
			last[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(last[fd], buf);
			free(last[fd]);
			last[fd] = tmp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = NULL;
	return (ft_reads_end(nbytes, &last[fd], &*line));
}
