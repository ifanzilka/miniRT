/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:37:11 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/01 18:39:59 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <libft.h>
# include <math.h>
# include <get_next_line.h>
# include <rgb.h>
# include <vectors.h>
# include <mlx.h>
# include <errors_rt.h>
# define INF INFINITY
# define MAX_DB 2147483648.0

typedef enum
{
	FALSE,
	TRUE
}	t_bool;

typedef	enum
{
	nothing,
	sphere,
	plane,
	triangle,
	square,
	cylinder
}	t_object;

typedef	enum
{
	point,
	direction
}	t_light_option;

typedef struct	s_range
{
	double		min;
	double		max;
}				t_range;

/*
**  Resolution
**  identifier:
**  x render size
**  y render size
**
**  Example:
**  "R 1920 1080"
*/

typedef struct	s_resolution
{
	int	width;
	int	height;
}				t_resolution;

/*
**  Ambient lightning
**  identifier: A
**  ambient lighting ratio in range [0.0,1.0]: 0.2
**  R,G,B colors in range [0-255]: 255, 255, 255
**
**  Example:
**  "A 0.2 255,255,255"
*/

typedef struct	s_ambient_lightning
{
	double	light;
	t_rgb	rgb;
}				t_ambient_lightning;

/*
**  Camera
**  identifier: c
** x,y,z coordinates of the view point: 0.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
** 0.0,0.0,1.0
** FOV : Horizontal field of view in degrees in range [0,180]
**  Example:
**  "c -50.0,0,20 0,0,1 70"
*/

typedef struct	s_camera
{
	t_xyz	cord;
	t_xyz	direction;
	double	fov;
}				t_camera;

/*
**  Light
**  identifier: l
** x,y,z coordinates of the light point: 0.0,0.0,20.6
** the light brightness ratio in range [0.0,1.0]: 0.6
** R,G,B colors in range [0-255]: 10, 0, 255
**  Example:
**  "l -40.0,50.0,0.0 0.6 10,0,255"
*/

typedef struct	s_light
{
	t_xyz	cord;
	double	intensive;
	t_rgb	rgb;
}				t_light;

/*
**  FIGURES
*/

/*
**  Sphere:
**  identifier: sp
** x,y,z coordinates of the sphere center: 0.0,0.0,20.6
** the sphere diameter: 12.6
** R,G,B colors in range [0-255]: 10, 0, 255
**  Example:
**  "sp 0.0,0.0,20.6 12.6 10,0,255"
*/

typedef struct	s_sphere
{
	t_xyz	coord_sph_centr;
	double	diametr;
	t_rgb	rgb;
	int		specular;
	double	reflective;
}				t_sphere;

/*
**  Plane:
**  identifier: pl
** x,y,z coordinates: 0.0,0.0,-10.0
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 0.0,0.0,1.0
** R,G,B colors in range [0-255]: 0, 0, 255
**  Example:
**  "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"
*/

typedef struct	s_plane
{
	t_xyz	cord;
	t_xyz	normal;
	t_rgb	rgb;
	int		specular;
	double	reflective;
}				t_plane;

/*
**  Square:
**  identifier: sq
** x,y,z coordinates of the square center: 0.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 1.0,0.0,0.0
** side size: 12.6
** R,G,B colors in range [0-255]: 255, 0, 255
**  Example:
**  "sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255"
*/

typedef struct	s_square
{
	t_xyz	cord;
	t_xyz	normal;
	double	side;
	t_rgb	rgb;
	int		specular;
	double	reflective;
}				t_square;

/*
**  Cylinder:
**  identifier: cy
** x,y,z coordinates: 50.0,0.0,20.6
** 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
** 0.0,0.0,1.0
** the cylinder diameter: 14.2
** the cylinder height: 21.42
** R,G,B colors in range [0,255]: 10, 0, 255
**  Example:
**  "cy 50.0,0.0,20.6 0.0,0.0,1.0  14.2 21.42 10,0,255"
*/

typedef struct	s_cylinder
{
	t_xyz	cord;
	t_xyz	normal;
	double	diameter;
	double	height;
	t_rgb	rgb;
	int		specular;
	double	reflective;
}				t_cylinder;

/*
**  Triangle:
**  identifier: tr
** x,y,z coordinates of the first point: 10.0,20.0,10.0
** x,y,z coordinates of the second point: 10.0,10.0,20.0
** x,y,z coordinates of the third point: 20.0,10.0,10.0
** R,G,B colors in range [0,255]: 0, 255, 255
**  Example:
**  "tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255"
*/

typedef struct	s_triangle
{
	t_xyz	first;
	t_xyz	second;
	t_xyz	third;
	t_rgb	rgb;
	int		specular;
	double	reflective;
}				t_triangle;

/*
**  Struct for cnt_object
*/

typedef struct	s_cnt_object
{
	int	r;
	int	a;
	int	c;
	int	l;
	int	sp;
	int	pl;
	int	sq;
	int	cy;
	int	tr;
}				t_cnt_object;

/*
**  Struct for rt
*/

typedef struct	s_rt
{
	pthread_mutex_t		mutex;
	t_cnt_object		cnt;
	t_resolution		reso;
	t_ambient_lightning	al;
	int					depth;
	t_camera			*camera;
	t_l_list			*ll_camera;
	t_list				*l_sphere;
	t_list				*l_light;
	t_list				*l_pl;
	t_list				*l_tr;
	t_list				*l_sq;
	t_list				*l_cy;
	t_list				*l_p;
}				t_rt;
void	        del_obj(void *p);
void			ft_clear_rt(t_rt *rt);
void			ft_error_rt(int n, t_rt *rt);

#endif
