/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:00:05 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/01 23:06:57 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** Добавляет элемент "new’ в начало
** списка.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*el;

// 	if (!(el = (t_list*)malloc(sizeof(t_list))))
// 		return (NULL);
// 	el->content = content;
// 	el->next = NULL;
// 	return (el);
// }