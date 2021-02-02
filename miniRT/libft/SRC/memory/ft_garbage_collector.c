/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:57:00 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/02 22:14:42 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		pointer_compare(void *ptr1, void *ptr2)
{
	return ((ptr1 == ptr2) ? 0 : 1);
}

static void		pointer_free(void *ptr)
{
	free(ptr);
}

/*
** This function collects all pointers to the allocated memory
** and clears them if necessary.
** This is implemented using a static list.
**
** The function accepts M_ADD when you need to add a pointer to the list,
** and M_REMOVE when you need to remove a pointer from the list.
** To clear the entire list of pointers, pass a null pointer!
*/

void			ft_garbage_collector(void *ptr, int action)
{
	static t_list	*collector = NULL;

	if (ptr == NULL)
		ft_lstclear(&collector, pointer_free);
	else if (action == M_ADD)
		ft_lstadd_front(&collector, ft_lstnew(ptr));
	else if (action == M_REMOVE)
		ft_lstdelel(&collector, ptr, pointer_compare, pointer_free);
}
