/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lst_cr_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:18:45 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:51:02 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_l_list	*ft_l_lst_cr_front(t_l_list **lst, void *content)
{
	t_l_list *new;

	if (!(new = ft_l_lsnew(content)))
		return (NULL);
	if (!lst)
		return (NULL);
	ft_l_lstadd_front(lst, new);
	return (new);
}
