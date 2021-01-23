/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:15:26 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 17:15:28 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>




static void    ft_intersect_ray_triangle(t_xyz o,t_xyz d,t_pixel *pixel,t_triangle *tr,t_range *range)
{
    t_xyz v1;
    t_xyz v2;
    t_xyz n;
    t_xyz v1d;
    double scal_v2_v1d;
    double t;

    v1 = ft_xyz_minus(tr->second_point,tr->first_point);
    v2 = ft_xyz_minus(tr->third_point,tr->first_point);
    n = ft_xyz_mult_xyz(v1,v2);
    v1d = ft_xyz_mult_xyz(v2,d);
    scal_v2_v1d = ft_xyz_scal(v1,v1d);
    if (fabs(scal_v2_v1d) < 0.01)
        return;
     t_xyz vec;

    vec = ft_xyz_minus(o, tr->first_point);
    double u;
    u = ft_xyz_scal(vec,v1d) / scal_v2_v1d;   
    if (u < 0.0 || u > 1.0)
        return ;
    t_xyz q_vec;
    q_vec = ft_xyz_mult_xyz(v1,vec); 
    double v;
    v = ft_xyz_scal(d,q_vec) / scal_v2_v1d;
    if (v < 0.0 || u + v > 1.0)
        return ;
    t = ft_xyz_scal(v2, q_vec) / scal_v2_v1d;
    if (t < pixel->t  && ft_in_range(range,t))
    {

        //printf("ku ku\n");
        //if (ft_xyz_scal() )
        pixel->t = t;
        pixel->rgb = tr->rgb;
        
        pixel->normal = n;
        pixel->specular = 0;//400;
        pixel->reflective = 0;
        pixel->id = triangle;
    }
}

void    ft_l_tr(t_all_obj *all_obj,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list      *l_tr;
    t_triangle  *tr;

    l_tr = all_obj->l_tr;
    while (l_tr)
    {
        tr = l_tr->content;
        ft_intersect_ray_triangle(o,d,pixel,tr, range);
        l_tr = l_tr->next;
    }
}