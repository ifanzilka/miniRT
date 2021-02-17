/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/02/18 02:04:35 by ifanzilka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>
#include <bmp.h>
#ifndef DEPTH
# define DEPTH 3
#endif
#ifndef TH
# define TH 512
#endif

/*
 * test th
 *
 * 400 -> 5.28 sec
 * 200 -> 4.96
 * 256 ->
 * 128 -> 5.17
 * 64 -> 5.08
 * 32 -> 5.33
 * 16 -> 5.23
 * 8 -> 5.6 sec
 * 4 -> 7 sec
 * 1 -> 13 sec
 */

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
	cy = argv.id * argv.rt->reso.height / TH;
	while (cy < (argv.id + 1) * argv.rt->reso.height / TH)
	{
		cx = 0;
		while (cx < rt->reso.width)
		{
			d = ft_init_d(&cx, &cy, rt);
			ft_trace_rgb(vars, cx, cy, &d);
			//ft_percent_render(cx, cy, rt->reso.width, rt->reso.height, argv.id);
			cx++;
		}
		cy++;
	}
	return (NULL);
}

void		ft_cr_thread(t_rt *rt, t_vars *vars)
{
	pthread_t	threads[TH];
	t_th_argv	argv[TH];
	int			result;
	int 		i;

	pthread_mutex_init(&rt->mutex, NULL);
	i = 0;
	while (i < TH)
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
	while (i < TH)
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
	ft_cr_thread(rt, vars);
	if (vars->bmp)
		ft_create_bmp(rt, &(vars->img));
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);

//	 int		cx;
//	 int		cy;
//	 t_xyz      d;
//	 clock_t begin = clock();
//	 double	time_spent;
//
//	 cx = 0;
//	 cy = 0;
//	 while (cy < rt->reso.height)
//	 {
//	 	while (cx < rt->reso.width)
//	 	{
//	 		d = ft_init_d(&cx, &cy, rt);
//	 		ft_trace_rgb(vars, cx, cy, &d);
//	 		//ft_percent_render(cx, cy, rt->reso.width, rt->reso.height);
//	 		cx++;
//	 	}
//	 	cx = 0;
//	 	cy++;
//	 }
//	 if (vars->bmp)
//	 	ft_create_bmp(rt, &(vars->img));
//	 else
//	 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
//    clock_t end = clock();
//    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//    printf("time : %f\n",time_spent);
	return (1);
}
