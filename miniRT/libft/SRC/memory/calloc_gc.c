/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:54:08 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/02 23:07:10 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*calloc_gc(size_t nmemb, size_t size)
{
	void	*pointer;

	pointer = ft_calloc(nmemb, size);
	ft_garbage_collector(pointer, M_ADD);
	return (pointer);
}
