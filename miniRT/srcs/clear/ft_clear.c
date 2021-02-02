/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:27:53 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/02 20:41:57 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>

void	del_obj(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

void	ft_clear_rt(t_rt *rt)
{
	ft_lstclear(&(rt->l_sphere), del_obj);
	ft_lstclear(&(rt->l_light), del_obj);
	ft_lstclear(&(rt->l_pl), del_obj);
	ft_lstclear(&(rt->l_tr), del_obj);
	ft_lstclear(&(rt->l_sq), del_obj);
	ft_lstclear(&(rt->l_cy), del_obj);
	ft_lstclear(&(rt->l_p), del_obj);
	ft_l_lstclear(&(rt->ll_camera), del_obj);
	ft_lstclear(&(rt->l_p), del_obj);
	free(rt);
}
