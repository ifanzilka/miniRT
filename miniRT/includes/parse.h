/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 22:25:55 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/12 22:28:33 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSE_H
#define PARSE_H
#include "ft_minirt.h"

int         ft_parse_rt(char *file);
t_rgb       ft_atoirgb(char *str);
t_xyz       ft_atoi_xyz(char *str, int *i);

#endif
