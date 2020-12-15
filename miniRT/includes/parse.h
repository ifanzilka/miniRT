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
t_rgb       ft_atoirgb(char *str,int *i);
int         ft_check_rgb(t_rgb rgb);
t_xyz       ft_atoi_xyz(char *str, int *i);
int         ft_check_xyz(t_xyz xyz_t);

#endif
