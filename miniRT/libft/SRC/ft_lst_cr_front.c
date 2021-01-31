/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cr_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:10:08 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 19:14:05 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_cr_front(t_list **lst, void *content)
{
	t_list *new;

	if (!(new = ft_lstnew(content)))
		return (NULL);
	if (!lst)
		return (NULL);
	new->next = *lst;
	*lst = new;
	return (new);
}
