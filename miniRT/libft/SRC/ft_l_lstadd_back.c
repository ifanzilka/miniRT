/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:56:42 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/27 13:57:15 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	ft_l_lstadd_back(t_l_list **lst,   t_l_list *new)
{
    t_l_list *tmp;

	if (!lst || !new)
		return ;
    tmp = *lst;
    if (!tmp)
    {
        *lst = new;
    }
    else
    {
        while (tmp->next)
        {
			tmp = tmp->next;
        }   
        tmp->next = new;
        new->prev = tmp;
    }
}

