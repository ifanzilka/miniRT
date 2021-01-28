/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:52:07 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/25 16:52:10 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <ft_minirt.h>
#include <ray_tracing.h>

void        ft_intersect_cy(t_xyz o, t_xyz d, t_pixel *pixel, t_range *range,t_cylinder *cy)
{
    //printf("1\n");
    double a;
    double b;
    double c;
    double discr;
    double t1;
    double t2;
    t_xyz minp;
    t_xyz maxp;

    t_xyz oc;
    minp = ft_xyz_minus(cy->cord,ft_xyz_mult_db(cy->normal
    ,cy->height / 2.0));
    maxp = ft_xyz_plus(cy->cord,ft_xyz_mult_db(cy->normal,cy->height / 2.0));

    oc = ft_xyz_minus(o,minp);
    a = ft_xyz_scal(d,d) - pow(ft_xyz_scal(d,cy->normal),2);
    c = ft_xyz_scal(oc,oc) - pow(ft_xyz_scal(oc,cy->normal),2) - pow(cy->diameter / 2.0,2);
    b = 2 * (ft_xyz_scal(d,oc) - ft_xyz_scal(d,cy->normal) * ft_xyz_scal(oc,cy->normal));

    if ((discr = b * b - 4 * a * c ) < 0.0)
        return;
    t1 = (-b + sqrt(discr)) / (2 * a);
    t2 = (-b - sqrt(discr)) / (2 * a);


    double m;

    t_xyz p1;
    t_xyz p2;

    p1 = ft_xyz_plus(o, ft_xyz_mult_db(d, t1 * 0.999));
    p2 = ft_xyz_plus(o, ft_xyz_mult_db(d, t2 * 0.999));


    //ft_intersect_pl(o,d,pixel,range,&maxxx);

    if (  t1 < pixel->t && ft_in_range(range,t1))
    {
        t_xyz n;
        t_xyz p;
        m = ft_xyz_scal(d,cy->normal) * t1 + ft_xyz_scal(oc,cy->normal);
        p = ft_xyz_plus(o, ft_xyz_mult_db(d, t1 * 0.999));

        n = ft_xyz_minus(p,minp);
        n = ft_xyz_minus(n,ft_xyz_mult_db(cy->normal,m));
        n = ft_xyz_normalaze(n);

          if (m < 0  || m  > cy->height) // || m  < ft_len_vect(ft_xyz_minus(p,cy->cord)))
        {
            
        }
        else
        {
            pixel->t = t1;

            pixel->rgb = cy->rgb;
            pixel->normal = n;//cy->normal;
            pixel->specular = cy->specular;
            pixel->reflective = cy->reflective;
           pixel->id = plane;
        }
    }
    if (t2 < pixel->t && ft_in_range(range,t2))
    {
        t_xyz n;
        t_xyz p;
        m = ft_xyz_scal(d,cy->normal) * t2 + ft_xyz_scal(oc,cy->normal);

        
        p = ft_xyz_plus(o, ft_xyz_mult_db(d, t2 * 0.999));
        n = ft_xyz_minus(p,minp);
        n = ft_xyz_minus(n,ft_xyz_mult_db(cy->normal,m));
        n = ft_xyz_normalaze(n);
        if (m < 0  || m  > cy->height) // || m  < ft_len_vect(ft_xyz_minus(p,cy->cord)))
        {
            
        }
        else
        {

            pixel->t = t2;
            pixel->rgb = cy->rgb;
            pixel->normal = n;//cy->normal;
            pixel->specular = cy->specular;
            pixel->reflective = cy->reflective;
            pixel->id = plane;
        }
    }
}

void        ft_l_cy(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list  *l_cy;
    t_cylinder *cy;
    
    l_cy = rt->l_cy;
    while (l_cy)
    {
        cy = l_cy->content;
        ft_intersect_cy(o, d, pixel,range,cy);
        l_cy = l_cy->next;
    }
}