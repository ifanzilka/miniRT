/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:09:22 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 17:09:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>


void    ft_intersect_pl(t_xyz o,t_xyz d,t_pixel *pixel,t_range *range, t_plane *pl)
{
    double t;
    double dn;
    double on;
    double dd;
 
    dd = -ft_xyz_scal(pl->normal, pl->cord);
    dn = ft_xyz_scal(pl->normal,d);
    on = ft_xyz_scal(pl->normal,o) + dd;
    if (dn == 0)
        return;
    if (fabs(dn) <  0.0000001)
        return;  
    //printf("ku ku\n");
    t = -on / dn;
    if (t < pixel->t  && ft_in_range(range,t))
    {
        //printf("ku ku\n");
        //if (ft_xyz_scal() )
        pixel->t = t;
        pixel->rgb = pl->rgb;
        pixel->normal = pl->normal;
        pixel->specular =pl->specular;//400;
        pixel->reflective = pl->reflective;
        pixel->id = plane;
    }
}

/*
**  ft_l_pl
** rt -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/

// void        ft_l_pl(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
// {
//     t_list  *l_pl;
//     t_plane *pl;

//     l_pl = rt->l_pl;
//     while (l_pl)
//     {
//         pl = l_pl->content;
//         ft_intersect_pl(o, d, pixel,range,pl);
//         l_pl = l_pl->next;
//     }
// }
// void    ft_add_color_li(t_cp_l *cp_l,t_xyz *n,t_light *li)
// {
//         cp_l->i =  li->intensive * cp_l->n_dot_l /( ft_len_vect(*n) * ft_len_vect(cp_l->l));
//         cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,ft_rgb_mult_db(li->rgb,cp_l->i));
// }

// void    ft_add_color_li_sp(t_cp_l *cp_l,t_xyz *v,t_light *li,int *sp)
// {
//         cp_l->i = li->intensive * pow(cp_l->r_dot_v/(ft_len_vect(cp_l->r) * ft_len_vect(*v)),*sp);
//         cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix,ft_rgb_mult_db(li->rgb,cp_l->i));
// }

// t_rgb  ft_compute_lighting(t_rt *rt,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
// {
  
//     t_list  *l_light;
//     t_light *li;
//     t_cp_l  *cp_l;

//     if (!(cp_l = malloc(sizeof(t_cp_l))) && !(ft_lst_cr_front(&rt->l_p, cp_l)))
//         ft_error_rt(err_malloc,rt);
//     cp_l->color_pix = ft_rgb_mult_db(pixel->rgb,rt->al.light);
// 	cp_l->color_pix = ft_rgb_plus_rgb(cp_l->color_pix, ft_rgb_mult_db(rt->al.rgb,rt->al.light));
//     l_light = rt->l_light;
//     while(l_light)
//     {
//         li = l_light->content;
//         cp_l->l =  ft_xyz_minus(li->cord,p);
//         cp_l->n_dot_l = ft_xyz_scal(n,cp_l->l);
//         if (cp_l->n_dot_l <= 0.0 && (pixel->id == plane || pixel->id == triangle))
//         {
            
//             n = ft_xyz_mult_db(n,-1.0);
//             cp_l->n_dot_l *= -1.0;//ft_xyz_scal(n,cp_l->l);
//         }
//         if (ClosestIntersection(rt, p , cp_l->l) != MAX_DB)
//         {
//             l_light = l_light->next;
//             continue;
//         }
//         if (cp_l->n_dot_l > -0.001)
//             ft_add_color_li(cp_l,&n,li);

//             if (pixel->specular > 1)
//             {
//                 cp_l->r = ft_reflect_ray(cp_l->l,n);
//                 cp_l->r_dot_v = ft_xyz_scal(cp_l->r, v);
//                 if (cp_l->r_dot_v > 0.0)
//                         ft_add_color_li_sp(cp_l,&v,li,&pixel->specular);
//             }
//         l_light = l_light->next;
//     }    
//     return (cp_l->color_pix);
// }