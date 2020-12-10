/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 00:13:31 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/02 00:53:34 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** IteraIterates список ’lst’ и применяет функцию
** ’f’ к содержимому каждого элемента. Создает новый
** список, полученный в результате последовательных применений
** функции ’f’. Функция " del " используется для
**удаления содержимого элемента, если это необходимо.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *head;
	t_list *node;

	if (!lst || !f)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (NULL);
	node = head;
	lst = lst->next;
	while (lst)
	{
		node->next = ft_lstnew(f(lst->content));
		if (!(node->next))
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		node = node->next;
		lst = lst->next;
	}
	return (head);
}
