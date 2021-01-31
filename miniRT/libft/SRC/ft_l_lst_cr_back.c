/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lst_cr_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:19:37 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/31 18:41:32 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_l_list	*ft_l_lst_cr_back(t_l_list **lst, void *content)
{
	t_l_list *new;

	if (!(new = ft_l_lsnew(content)))
		return (NULL);
	if (!lst)
		return (NULL);
	ft_l_lstadd_back(lst, new);
	return (new);
}
