/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:52:04 by bmarilli          #+#    #+#             */
/*   Updated: 2020/11/02 18:34:13 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ENG
*/

/*
** RUS
**
** del -> Адрес функции, используемой для удаления
** содержимого.
** Удаляет и освобождает данного элемента и каждого
** преемником этого элемента, используя функцию "del"
**и free(3).
** Наконец, указатель на список должен быть установлен в
** значение NULL.
*/

/*
** OLD
**
**	void	ft_lstclear(t_list **lst, void (*del)(void*))
**	{
**		t_list	*cur;
**		t_list	*tmp;
**
**		if (!lst || !del)
**			return ;
**		cur = *lst;
**		while (cur)
**		{
**			tmp = cur;
**			cur = cur->next;
**			ft_lstdelone(tmp, del);
**		}
**		*lst = NULL;
**	}
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur)
	{
		del(cur->content);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	*lst = NULL;
}
