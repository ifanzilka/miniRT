/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/17 15:41:20 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>
#include <bmp.h>
#ifndef DEPTH
# define DEPTH 3
#endif

/*
**  Cicle for all pixel
**
** Example:
** 600 600
*/

static void	ft_trace_rgb(t_vars *vars, int cx, int cy, t_xyz *d)
{
	t_rgb	rgb;
	t_rt	*rt;

	rt = vars->rt;
	rgb = ft_ray_trace(rt, rt->camera->cord, *d, DEPTH);
	my_mlx_pixel_put(&(vars->img), cx, cy,
	create_rgb(rgb.red, rgb.green, rgb.blue));
}

void		*ft_cicle_th(void *argvs)
{
	t_th_argv	argv;
	t_rt		*rt;
	t_vars		*vars;
	int		cx;
	int		cy;
	t_xyz	d;

	argv = * (t_th_argv *)argvs;
	rt = argv.rt;
	vars = argv.vars;
	cy = argv.id * argv.rt->reso.height / 4;
	while (cy < (argv.id + 1) * argv.rt->reso.height / 4)
	{
		cx = 0;
		while (cx < rt->reso.width)
		{
			d = ft_init_d(&cx, &cy, rt);
			ft_trace_rgb(vars, cx, cy, &d);
			ft_percent_render(cx, cy, rt->reso.width, rt->reso.height, argv.id);
			cx++;
		}
		cy++;
	}
	return (NULL);
}

void		ft_cr_thread(t_rt *rt, t_vars *vars)
{
	pthread_t	threads[4];
	t_th_argv	argv[4];
	int			result;
	int 		i;

	pthread_mutex_init(&rt->mutex, NULL);
	i = 0;
	while (i < 4)
	{
		argv[i].id = i;
		argv[i].vars = vars;
		argv[i].rt = rt;
		result = pthread_create(&threads[i], NULL, ft_cicle_th, &argv[i]);
		if (result != 0)
		{
			perror("Creating thread ");
			ft_error_rt(-1 , rt);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		result = pthread_join(threads[i], NULL);
		if (result != 0)
		{
			perror("Join thread ");
			ft_error_rt(-1 , rt);		
		}
		i++;
	}
    //ft_garbage_collector(NULL, 1);
}

int			cicle_for_pixel(t_rt *rt, t_vars *vars)
{
	clock_t begin;
	clock_t end;
	double	time_spent;

	begin = clock();
	ft_cr_thread(rt, vars);
	if (vars->bmp)
		ft_create_bmp(rt, &(vars->img));
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time : %f\n",time_spent);
	// int		cx;
	// int		cy;
	// t_xyz	d;

	// cx = 0;
	// cy = 0;
	// while (cy < rt->reso.height)
	// {
	// 	while (cx < rt->reso.width)
	// 	{
	// 		d = ft_init_d(&cx, &cy, rt);
	// 		ft_trace_rgb(vars, cx, cy, &d);
	// 		ft_garbage_collector(NULL, 1);
	// 		ft_percent_render(cx, cy, rt->reso.width, rt->reso.height);
	// 		cx++;
	// 	}
	// 	cx = 0;
	// 	cy++;
	// }
	// if (vars->bmp)
	// 	ft_create_bmp(rt, &(vars->img));
	// else
	// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (1);
}
