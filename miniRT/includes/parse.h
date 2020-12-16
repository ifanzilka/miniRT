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
int             ft_check_normalizate(t_xyz xyz);
t_xyz       ft_atoi_xyz(char *str, int *i);
int         ft_check_xyz(t_xyz xyz_t);
int         ft_parse_R(t_all_obj *my,char *str);
int         ft_parse_A(t_all_obj *my,char *str);
int         ft_parse_c(t_all_obj *my,char *str);
int         ft_parse_l(t_all_obj *my,char *str);
int         ft_parse_sp(t_all_obj *my,char *str);
int         ft_parse_cy(t_all_obj *my,char *str);
int         ft_parse_pl(t_all_obj *my , char *str);
int         ft_parse_sq(t_all_obj *my , char *str);
int         ft_parse_tr(t_all_obj *my , char *str);

#endif
