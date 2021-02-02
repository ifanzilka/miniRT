/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:34:03 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/28 23:34:05 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include "ray_tracing.h"

void    ft_add_color_li(t_cp_l *cp_l,t_xyz *n,t_light *li)
{
    if (cp_l->n_dot_l > 0.1)
    {
        cp_l->i =  li->intensive * cp_l->n_dot_l /( ft_len_vect(*n) * ft_len_vect(cp_l->l));
        cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,ft_rgb_mult_db(li->rgb,cp_l->i));
    }
}

void    ft_add_color_li_sp(t_cp_l *cp_l,t_xyz *v,t_light *li,t_xyz *n,int *sp)
{
    if (*sp > 1)
    {
        cp_l->r = ft_reflect_ray(cp_l->l,*n);
        cp_l->r_dot_v = ft_xyz_scal(cp_l->r, *v);
        if (cp_l->r_dot_v > 0.0)
        {
            cp_l->i = li->intensive * pow(cp_l->r_dot_v/(ft_len_vect(cp_l->r) * ft_len_vect(*v)),*sp);
            cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,ft_rgb_mult_db(li->rgb,cp_l->i));
        }
    }    
}

void    ft_init_color(t_rt *rt,t_cp_l *cp_l,t_pixel *pixel)
{
    cp_l->color_pix = ft_rgb_mult_db(pixel->rgb,rt->al.light);
	cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix, ft_rgb_mult_db(rt->al.rgb,rt->al.light));
}

void    ft_init_vectors_light(t_light *li,t_cp_l *cp_l,t_pixel *pixel,t_xyz *n, t_xyz *p)
{
    cp_l->l =  ft_xyz_minus(li->cord,*p);
    cp_l->n_dot_l = ft_xyz_scal(*n,cp_l->l);
    if (cp_l->n_dot_l <= 0.0 && (pixel->id == plane || pixel->id == triangle))
    {
            *n = ft_xyz_mult_db(*n,-1.0);
            cp_l->n_dot_l *= -1.0;//ft_xyz_scal(n,cp_l->l);
    }
}

/*
**  o vec -> point in obk=ject
**  d -> vec in light
**
**
*/

double closestintersection(t_rt *rt,t_xyz o, t_xyz d)
{
    t_pixel pixel;
    t_range range;

    range.min = 0.000001;
    range.max = 0.999999;
    pixel.t = MAX_DB;
    ft_iter_obj_close(rt, &pixel, o, d,&range);
    return (pixel.t);
}


t_rgb  ft_compute_lighting(t_rt *rt,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
{
    t_list  *l_light;
    t_light *li;
    t_cp_l  *cp_l;
  
    if (!(cp_l = malloc_gc(sizeof(t_cp_l))))
        ft_error_rt(err_malloc,rt);
    ft_init_color(rt,cp_l,pixel);
    l_light = rt->l_light;
    while(l_light)
    {
        li = l_light->content;
        ft_init_vectors_light(li,cp_l, pixel, &n, &p);  

        if (closestintersection(rt, p ,cp_l->l) != MAX_DB)
        {
            l_light = l_light->next;
            continue;
        }
        ft_add_color_li(cp_l,&n,li);
        ft_add_color_li_sp(cp_l,&v,li,&n,&pixel->specular);
        l_light = l_light->next;
    }
   //free(cp_l);
    return (cp_l->color_pix);
}

// t_rgb  ft_compute_lighting(t_rt *rt,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
// {
//     t_list  *l_light;
//     t_light *li;
//     t_cp_l  cp_l;
  
//     ft_init_color(rt,&cp_l,pixel);
//     l_light = rt->l_light;
//     while(l_light)
//     {
//         li = l_light->content;
//         ft_init_vectors_light(li,&cp_l, pixel, &n, &p);  
//         if (ClosestIntersection(rt, p ,cp_l.l) != MAX_DB)
//         {
//             l_light = l_light->next;
//             continue;
//         }
//         ft_add_color_li(&cp_l,&n,li);
//         ft_add_color_li_sp(&cp_l,&v,li,&n,&pixel->specular);
//         l_light = l_light->next;
//     }
//    //free(cp_l);
//     return (cp_l.color_pix);
// }