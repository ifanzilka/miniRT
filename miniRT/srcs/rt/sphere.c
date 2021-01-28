/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:49:01 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 16:49:02 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>

/*
**  Sphere:
** P - point lutch
** C - Center sphere
** 
** |P - C| = r
** 
**  <P - C, P - C > = r ^ 2
**
** D = V - O
**
** and  P = O + t * D
** 
*/

double  ft_intersect_ray_sphere(t_xyz o, t_xyz d,t_pixel *pixel,t_sphere *spher,t_range *range)
{
    t_xyz oc;
    t_kf_abc abc;
    t_xyz p1;

    oc = ft_xyz_minus(o,spher->coord_sph_centr);    
    abc.a = ft_xyz_scal(d,d);
    abc.b = 2 * ft_xyz_scal(oc,d);
    abc.c = ft_xyz_scal(oc,oc) - pow(spher->diametr ,2);
    if ((abc.discr = abc.b * abc.b - 4 * abc.a * abc.c ) < 0.0)
        return(MAX_DB);
    abc.t1 = (-abc.b + sqrt(abc.discr)) / (2*abc.a);
    abc.t2 = (-abc.b - sqrt(abc.discr)) / (2*abc.a);
   
    if((abc.t1 >= 0.0 && abc.t2 <= 0.0) || (abc.t2 >= 0.0 && abc.t1 <= 0.0)) 
    {
        if ( (abc.t1) < pixel->t  && ft_in_range(range,abc.t1))
        {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            //pixel->cor = spher->coord_sph_centr;
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t * 0.9999));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal =  n;
            //pixel->normal = ft_xyz_normalaze(pixel->normal);
            return (0.0);


        }
        else if ((abc.t2 < pixel->t) && ft_in_range(range,abc.t2))
        {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t2;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t * 0.9999));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal =  n;
            //pixel->normal = ft_xyz_normalaze(pixel->normal);
            return (0.0);

        }
        return (0.0);
    }
    else if ((abc.t1 < abc.t2) && (abc.t1 < pixel->t) && ft_in_range(range,abc.t1))
    {
    
            //printf("!!!!\n");
            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            //pixel->cor = spher->coord_sph_centr;
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal =  n;
            //pixel->normal = ft_xyz_normalaze(pixel->normal);
    }
    else if ((abc.t2 <= abc.t1) && (abc.t2 < pixel->t) && ft_in_range(range,abc.t2))
    {
       // printf("!!!!\n");

        if (ft_len_vect(oc) < spher->diametr) 
        {

            pixel->rgb = spher->rgb;
            pixel->t = abc.t1;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal = ft_xyz_normalaze(pixel->normal);    
            pixel->normal =  n;
        }
        else {
            pixel->rgb = spher->rgb;
            pixel->t = abc.t2;
            
            pixel->specular = spher->specular;
            pixel->reflective = spher->reflective;
            p1 = ft_xyz_plus(o,ft_xyz_mult_db(d,pixel->t));
            t_xyz n;
            n = ft_xyz_minus(p1,spher->coord_sph_centr);
            pixel->normal =  n;//ft_xyz_div_db(n,ft_len_vect(n));
        }
        //return (t2);
    } 
    return (0.0);  
}


/*
**  ft_l_sphere
**  rt -> rt
**  pixel -> adress in pixel param
**  o -> cord start in lutch
**  d -> vec >>>>
**  (no back point)
*/

void       ft_l_sp(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list      *l_sp;
    t_sphere    *spher;

    l_sp = rt->l_sphere;
    while (l_sp)
    {
        spher = l_sp->content;
        ft_intersect_ray_sphere(o,d,pixel,spher, range);
        l_sp = l_sp->next;
    }
}

