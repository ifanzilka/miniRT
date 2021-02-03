/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:42:27 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/23 17:42:32 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <ray_tracing.h>


// void     ft_intersect_ray_square(t_xyz o,t_xyz d,t_pixel *pixel,t_square *sq, t_range *range)
// {   
//     t_pixel pixel_loc;
//     t_plane pl;
//     double t;

//     pixel_loc.t =  MAX_DB;
//     pl.normal = sq->normal;
//     pl.cord = sq->cord;
//     ft_intersect_pl( o, d, &pixel_loc,range,&pl);
//     if (pixel_loc.t == MAX_DB)
//         return;  
//     t = pixel_loc.t;
//     if (t < pixel->t  && ft_in_range(range,t))
//     {
//         t_xyz p;
//         t_range range2;
//         range2.min = -sq->side / 4.0;
//         range2.max = sq->side / 4.0;
//         p = ft_xyz_plus(o, ft_xyz_mult_db(d, t * 0.999));
//         if (ft_in_range(&range2,p.x -  sq->cord.x) && ft_in_range(&range2,p.y- sq->cord.y) && ft_in_range(&range2,p.z - sq->cord.z)  )
//         {
//             pixel->t = t;
//             pixel->rgb = sq->rgb;
//             pixel->normal = sq->normal;
//             pixel->specular = sq->specular;
//             pixel->reflective = sq->reflective;
//             pixel->id = plane;
//         }
//     }
// }

void     ft_intersect_ray_square(t_lutch luc,t_pixel *pixel,t_square *sq, t_range *range)
{   
    t_pixel pixel_loc;
    t_plane pl;
    double t;
    t_xyz o;
    t_xyz dir;

    o = luc.o;
    dir = luc.d;
    pixel_loc.t =  MAX_DB;
    pl.normal = sq->normal;
    pl.cord = sq->cord;
    ft_intersect_pl( luc, &pixel_loc,range,&pl);
    if (pixel_loc.t == MAX_DB)
        return;  
    t = pixel_loc.t;

    t_xyz p;
    p = ft_xyz_plus(o,ft_xyz_mult_db(dir,t * 0.999));
    t_xyz n_r;
    t_xyz n_up;

    t_xyz a;
    t_xyz b;
    t_xyz c;
    t_xyz d;

    t_xyz c_d;
    t_xyz a_b;

    n_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0},sq->normal);
    n_up = ft_xyz_mult_xyz(sq->normal,n_r);

    c_d = ft_xyz_plus(sq->cord,ft_xyz_mult_db(n_r ,sq->side / 2));
    a_b = ft_xyz_minus(sq->cord,ft_xyz_mult_db(n_r ,sq->side/ 2));
    
    a = ft_xyz_minus(a_b,ft_xyz_mult_db(n_up,sq->side / 2));
    b = ft_xyz_plus(a_b,ft_xyz_mult_db(n_up,sq->side / 2));

    d = ft_xyz_minus(c_d,ft_xyz_mult_db(n_up,sq->side / 2));
    c = ft_xyz_plus(c_d,ft_xyz_mult_db(n_up,sq->side / 2));

    // printf("a : %f, %f, %f \n",a.x,a.y,a.z);
    // printf("b : %f, %f, %f \n",b.x,b.y,b.z);
    // printf("c : %f, %f, %f \n",c.x,c.y,c.z);
    // printf("d : %f, %f, %f \n",d.x,d.y,d.z);


    t_xyz ab;
    t_xyz bc;
    t_xyz cd;
    t_xyz da;

    ab = ft_xyz_minus(b,a);
    bc = ft_xyz_minus(c,b);
    cd = ft_xyz_minus(d,c);
    da = ft_xyz_minus(a,d);

    t_xyz normal_ab;
    t_xyz normal_bc;
    t_xyz normal_cd;
    t_xyz normal_da;

    normal_ab = ft_xyz_mult_xyz(ab,sq->normal);
    normal_bc = ft_xyz_mult_xyz(bc,sq->normal);
    normal_cd = ft_xyz_mult_xyz(cd,sq->normal);
    normal_da = ft_xyz_mult_xyz(da,sq->normal);

    double ans = 0;

    ans = (p.x - a.x) * normal_ab.x + (p.y - a.y) * normal_ab.y + (p.z - a.z) * normal_ab.z;
    ans *= (d.x - a.x) * normal_ab.x + (d.y - a.y) * normal_ab.y + (p.z - a.z) * normal_ab.z;

    if (ans < 0)
        return;
    ans = (p.x - b.x) * normal_bc.x + (p.y - b.y) * normal_bc.y + (p.z - b.z) * normal_bc.z;
    ans *= (a.x - b.x) * normal_bc.x + (a.y - b.y) * normal_bc.y + (a.z - b.z) * normal_bc.z;
    if (ans < 0)
        return;
   
    ans =     (p.x - c.x) * normal_cd.x + (p.y - c.y) * normal_cd.y + (p.z - c.z) * normal_cd.z;
    ans *= (a.x - c.x) * normal_cd.x + (a.y - c.y) * normal_cd.y + (a.z - c.z) * normal_cd.z ;
    if (ans < 0)
        return;

    ans = (p.x - d.x) * normal_da.x + (p.y - d.y) * normal_da.y + (p.z - d.z) * normal_da.z;
    ans *= (b.x - d.x) * normal_da.x + (b.y - d.y) * normal_da.y + (b.z - d.z) * normal_da.z;

     if (ans < 0)
        return;

    //if ( (p.x - a.x) * normal_ab.x + (p.y - a.y) * normal_ab.y + (p.z - a.z) * normal_ab.z >= 0 && (d.x - a.x) * normal_ab.x + (d.y - a.y) * normal_ab.y + (p.z - a.z) * normal_ab.z < 0)
      //  return;
    //if ( (d.x - a.x) * normal_ab.x + (d.y - a.y) * normal_ab.y + (p.z - a.z) * normal_ab.z >= 0 && ans != 1)
      //  return;

    // ans = 0;
    // if ( (p.x - b.x) * normal_bc.x + (p.y - b.y) * normal_bc.y + (p.z - b.z) * normal_bc.z >= 0)
    //     ans = 1;
    // if ( (a.x - b.x) * normal_bc.x + (a.y - b.y) * normal_bc.y + (a.z - b.z) * normal_bc.z >= 0 && ans != 1)
    //     return; 

    //   ans = 0;
    // if ( (p.x - c.x) * normal_cd.x + (p.y - c.y) * normal_cd.y + (p.z - c.z) * normal_cd.z >= 0)
    //     ans = 1;
    // if ( (a.x - c.x) * normal_cd.x + (a.y - c.y) * normal_cd.y + (a.z - c.z) * normal_cd.z >= 0 && ans != 1)
    //     return;

    //     ans = 0;
    // if ((p.x - d.x) * normal_da.x + (p.y - d.y) * normal_da.y + (p.z - d.z) * normal_da.z >= 0)
    //     ans = 1;
    // if ( (b.x - d.x) * normal_da.x + (b.y - d.y) * normal_da.y + (b.z - d.z) * normal_da.z >= 0 && ans != 1)
    //     return;  

      
    if (t < pixel->t  && ft_in_range(range,t))
    {
        t_xyz p;
        t_range range2;
        range2.min = -sq->side / 2;
        range2.max = sq->side  / 2;
        p = ft_xyz_plus(o, ft_xyz_mult_db(dir, t * 0.999));
        if (ft_in_range(&range2,p.x -  sq->cord.x) && ft_in_range(&range2,p.y- sq->cord.y) && ft_in_range(&range2,p.z - sq->cord.z)  )
        {
            pixel->t = t;
            pixel->rgb = sq->rgb;
            pixel->normal = sq->normal;
            pixel->specular = sq->specular;
            pixel->reflective = sq->reflective;
            pixel->id = triangle;
        }
    }

    // pixel->t = t;
    // pixel->rgb = sq->rgb;
    // pixel->normal = sq->normal;
    // pixel->specular = sq->specular;
    // pixel->reflective = sq->reflective;
    // pixel->id = plane;           

}


void    ft_l_sq(t_rt *rt,t_pixel *pixel,t_lutch luc,t_range *range)
{
    t_list      *l_sq;
    t_square *sq;

    l_sq = rt->l_sq;
    while (l_sq)
    {
        sq = l_sq->content;
        ft_intersect_ray_square(luc,pixel,sq, range);
        l_sq = l_sq->next;
    }
}