/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 22:25:55 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 19:02:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <ft_minirt.h>
# include <math.h>

int		ft_parse_rt(char *file, int argc);
t_rgb	ft_atoirgb(char *str, int *i);
int		ft_check_rgb(t_rgb rgb);
t_xyz	ft_atoi_xyz(char *str, int *i);
int		ft_check_xyz(t_xyz xyz_t);
int		ft_parse_r(t_rt *rt, char *str);
int		ft_parse_a(t_rt *rt, char *str);
int		ft_parse_c(t_rt *rt, char *str);
int		ft_parse_l(t_rt *rt, char *str);
int		ft_parse_sp(t_rt *rt, char *str);
int		ft_parse_cy(t_rt *rt, char *str);
int		ft_parse_pl(t_rt *rt, char *str);
int		ft_parse_sq(t_rt *rt, char *str);
int		ft_parse_tr(t_rt *rt, char *str);

#endif
