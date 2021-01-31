/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:56:16 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 19:16:48 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_l_lstadd_front(t_l_list **lst, t_l_list *new)
{
	t_l_list *tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!(tmp))
		*lst = new;
	else
	{
		new->next = *lst;
		new->prev = tmp->prev;
		tmp->prev = new;
		*lst = new;
	}
}
