/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:54:01 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/02 20:54:03 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*malloc_gc(size_t sizemem)
{
	void	*pointer;

	pointer = malloc(sizemem);
	ft_garbage_collector(pointer, M_ADD);
	return (pointer);
}
