/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:09:45 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 19:17:55 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
** ENG
*/

/*
** RUS
**
** Добавляет элемент "new’ в конец
** списка.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur;

	if (!(lst))
		return ;
	cur = *lst;
	if (!cur)
		*lst = new;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
