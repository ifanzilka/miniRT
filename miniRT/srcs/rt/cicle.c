/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cicle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:16:21 by bmarilli          #+#    #+#             */
/*   Updated: 2021/01/15 11:16:23 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include <ft_minirt.h>
#include "ray_tracing.h"
# ifndef depth
#define depth 3
#endif

int     ft_in_range(t_range *range, double a)
{
    if (a >= range->min && a <= range->max)
        return (1);
    return (0);    
} 

/*
** cx and cy -> coordinat pixel in window system
*/

/*
**  Converter x Screen coordinat to decart coordinat
**
**  cx -> coordinat x for Scr
**  width -> width window
**  xmin  -> minimal x in decart system
**  xmax  -> maximal x in decart system
**  return -> x for decart system
*/

double  ft_convert_scr_to_dec_x(int cx, int width, double xmin, double xmax)
{
    double x;
    double xsize;
    double w;

    w = width;
    xsize = xmax - xmin;
    x = xmin + (cx / w) * xsize;
    return (x);
    //return ((double)cx - (double)width / 2);
}

/*
**  Converter y Screen coordinat to decart coordinat
**
**  cy -> coordinat y for Scr
**  width -> width window
**  ymin  -> minimal y in decart system
**  ymax  -> maximal y in decart system
**  return -> y for decart system
*/

double  ft_convert_scr_to_dec_y(int cy, int height, double  ymin, double  ymax)
{
    double y;
    double ysize;
    double h;
    
    h = height;
    ysize = ymax - ymin;
    y = ymax - (cy / h) * ysize;
    return (y);
}

/*
**  Create viewport vector
**
**  x -> coordinat 
**  y -> coordinat
**  width window
**  height window
**  Vx = Cx * Vw/Cw
**  Vy = Cy * Vh/Ch
**  Vz = d
**  z -> z
**  return -> vector xyz
*/

void  ft_rt_xy_convert(int *cx,int *cy, double *x,double *y,t_rt *rt)
{
    double width;
    double height;

    width = rt->reso.width;
    height = rt->reso.height;
     *x =  ft_convert_scr_to_dec_x(*cx, width, -(width / 2), width / 2);
     *y =  ft_convert_scr_to_dec_y(*cy, height, -(height / 2),height / 2);
}

void ft_iter_obj(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    ft_l_sp(rt, pixel, o, d,range);
    ft_l_pl(rt, pixel, o, d,range);
    ft_l_tr(rt,pixel,o, d,range);
    ft_l_sq(rt,pixel,o, d,range);
    ft_l_cy(rt,pixel,o, d,range);
}

t_xyz      ft_create_v(double x, double y, int width, int height, double z)
{
    t_xyz v;

    (void) width;
    (void)  height;
    (void) z;

    v.x =   x  / height;//- (width/2);
    v.y =   y * (1.0/height); //(height/2)-y;
    v.z =   z;
    return (v);
}

/*
**  Reflected relative to n ray
**  r - vec
**  n - normal
**  /return 2 * N * dot(N, R) - R;
*/

 t_xyz   ft_reflect_ray(t_xyz r, t_xyz n) 
 {
    t_xyz res;

    res = ft_xyz_mult_db(n,2);
    res = ft_xyz_mult_db(res,ft_xyz_scal(n,r));
    res = ft_xyz_minus(res,r);
    return (res);
}


/*  
**   ft_recurse_color
**
**   return local_color * (1 - r) + reflected_color * r
*/

t_rgb   ft_recurse_color(t_rgb  ref_col, t_rgb  loc_col, double reflective)
{
    t_rgb res;

    res = ft_rgb_mult_db(loc_col,1 - reflective);
    res = ft_rgb_plus_rgb(res, ft_rgb_mult_db(ref_col,reflective));
    return (res);
}


/*
**  o vec -> point in obk=ject
**  d -> vec in light
**
**
*/

double ClosestIntersection(t_rt *rt,t_xyz o, t_xyz d)
{
    t_pixel pixel;
    t_range range;

    range.min = 0.000001;
    range.max = 0.999999;
    pixel.t = MAX_DB;
    ft_iter_obj(rt, &pixel, o, d,&range);
    return (pixel.t);
}

/*
**   ft_compute_lighting
**  rtect
**  point (p) in object
**  n -> normal vec
**  v -> vec in (-d)
*/

typedef struct s_cp_l
{
    double      i;
    double      n_dot_l;
    double      r_dot_v; 
    t_rgb       color_pix;
    t_xyz       l;    
    t_xyz       r;
}              t_cp_l;



void        ft_l_pl(t_rt *rt,t_pixel *pixel,t_xyz o,t_xyz d,t_range *range)
{
    t_list  *l_pl;
    t_plane *pl;

    l_pl = rt->l_pl;
    while (l_pl)
    {
        pl = l_pl->content;
        ft_intersect_pl(o, d, pixel,range,pl);
        l_pl = l_pl->next;
    }
}
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

t_rgb  ft_compute_lighting(t_rt *rt,t_xyz p, t_xyz n,t_xyz v,t_pixel *pixel)
{
    t_list  *l_light;
    t_light *li;
    t_cp_l  *cp_l;

    if (!(cp_l = malloc(sizeof(t_cp_l))) && !(ft_lst_cr_front(&rt->l_p, cp_l)))
        ft_error_rt(err_malloc,rt);
    ft_init_color(rt,cp_l,pixel);
    
    l_light = rt->l_light;
    while(l_light)
    {
        li = l_light->content;
        ft_init_vectors_light(li,cp_l, pixel, &n, &p);    
        if (ClosestIntersection(rt, p , cp_l->l) != MAX_DB)
        {
            l_light = l_light->next;
            continue;
        }
        ft_add_color_li(cp_l,&n,li);
        ft_add_color_li_sp(cp_l,&v,li,&n,&pixel->specular);
        l_light = l_light->next;
    }    
    return (cp_l->color_pix);
}


/*
**  ft_ray_trace
**  rt -> struct in rt
**  vec o -> point start in lutch (camera)
**  vec d -> lutch in ray_trace
**  range -> min and max kf for d 
**  p = o + D * t 
**  return (rgb) color in pixel
*/

t_rgb     ft_ray_trace(t_rt *rt,t_xyz o,t_xyz d,t_range range,int rec)
{
    t_xyz   p;
    t_xyz   r;
    t_pixel *pixel;
    t_rgb   ref_color;

    if (!(pixel = malloc(sizeof(t_pixel))) && !(ft_lst_cr_front(&rt->l_p, pixel)))
        ft_error_rt(err_malloc,rt);
    pixel->t = MAX_DB;
    pixel->rgb = ft_rgb_mult_db(rt->al.rgb,rt->al.light);
    ft_iter_obj(rt, pixel, o, d,&range);
    if (pixel->t == MAX_DB)
        return (pixel->rgb);
    //pixel.normal = ft_xyz_mult_db(pixel.normal,-1.0);    
    p = ft_xyz_plus(o, ft_xyz_mult_db(d, pixel->t * 0.9999));
    pixel->rgb = ft_compute_lighting(rt,  p, pixel->normal,ft_xyz_mult_db(d, -1.0),pixel);
    if (rec <=  0 || pixel->reflective <= 0.01)
        return(pixel->rgb);
    r = ft_reflect_ray(ft_xyz_mult_db(d,-1.0),pixel->normal);
    ref_color = ft_ray_trace(rt, p, r,range,rec - 1);
    return(ft_recurse_color(ref_color, pixel->rgb, pixel->reflective));
}

t_xyz   ft_create_vec_d(t_rt *rt, double x, double y)
{
    t_xyz   c_r;
    t_xyz   c_up;
    t_xyz   d;
    t_xyz   v;
    double  kf;
    
    rt->camera->direction = ft_xyz_normalaze(rt->camera->direction);
    kf  =  2 * tan(rt->camera->fov / 2 * 3.14 / 180);
    x *= kf;
    y *= kf;
    v = ft_create_v(x, y, rt->reso.width, rt->reso.height, 1);
    c_r = ft_xyz_mult_xyz((t_xyz){0.0, 1.0, 0.0},rt->camera->direction);
    c_up = ft_xyz_mult_xyz(rt->camera->direction,c_r);
    d = ft_r_u_n_mult_xyz(c_r,c_up,rt->camera->direction,v);
    return (d);
}

t_xyz ft_init_d(int *cx,int *cy,t_rt *rt)
{
    double x;
    double y;

    ft_rt_xy_convert(cx,cy,&x,&y,rt);
    return (ft_create_vec_d(rt , x ,y));
}

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/

int     cicle_for_pixel(t_rt *rt,t_vars *vars)
{
    clock_t begin = clock();
    int cx;
    int cy;
    t_rgb rgb;
    t_xyz d;
   
    cx = 0;
    cy = 0;
    while (cy < rt->reso.height)
    {
        while(cx < rt->reso.width)
        {    
            d = ft_init_d(&cx,&cy,rt);
            rgb = ft_ray_trace(rt, rt->camera->cord, d ,(t_range){0.0001,MAX_DB},depth);
            mlx_pixel_put(vars->mlx,vars->win,cx,cy,create_rgb(rgb.red,rgb.green,rgb.blue));
            cx++;
        }
        cx = 0;
        cy++;
    }  
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TIME %f sec\n",time_spent);
    return (1);
}
