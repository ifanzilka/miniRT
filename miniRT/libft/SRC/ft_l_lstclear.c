/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:52:24 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:53:51 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_l_lstclear(t_l_list **lst, void (*del)(void*))
{
	t_l_list	*cur;
	t_l_list	*tmp;

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
