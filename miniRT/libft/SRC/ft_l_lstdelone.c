/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:56:23 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/27 17:56:33 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RUS
**
** del -> Адрес функции, используемой для удаления
** содержимого.
** Принимает в качестве параметра элемент и освобождает
** память содержимого элемента, используя функцию
** ’del’, заданную в качестве параметра, и освобождает элемент.
** Память о "следующем" не должна быть освобождена.
*/

void	ft_l_lstdelone(t_l_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}