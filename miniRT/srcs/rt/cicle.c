#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include "mlx.h"

#define MAX_DB 2147483647.0

/*
**  Fun create_rgb
**  
**  Example:
** r -> 155  (10011011)
** g -> 240  (11110000)
** b -> 100  (01100100)
** (r << 16) -> (100110110000000000000000) (plus 16 zero bit)
** (g << 8) -> (1111000000000000)
** b ->   (01100100)
** "l" -> oretion OR (bits)
**    (100110110000000000000000)
** or (000000001111000000000000)
**    (000000000000000001100100)
** res(100110111111000001100100)
*/


typedef struct  s_pixel 
{
    double          t;
    t_rgb           rgb;
    t_xyz           spher_cor;

}                t_pixel;


int		create_rgb( int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

/*
** 0xFF -> all bits (1)
*/



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

t_xyz      ft_create_v(double x, double y, int width, int height, double z)
{
    t_xyz v;

    (void) width;
    (void)  height;

    v.x =  x / width;
    v.y =  y / height;
    v.z =  z;
    return (v);
}

/*
**  Create  vector xyz
**
**  x -> coordinat 
**  y -> coordinat
**  z -> coordinat
**  return -> vector xyz
*/

t_xyz      ft_create_xyz(double x, double y,double z)
{
    t_xyz o;

    o.x = x;
    o.y = y;
    o.z = z;
    return (o);
}

/*
**  Operation minus  vector xyz
**
**   a - b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_minus(t_xyz a, t_xyz b)
{
    t_xyz res;

    
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

/*
**  Operation plus  vector xyz
**
**   a + b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_plus(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return (res);
}

/*
**  Operation mult  vector xyz
**
**   a * b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_mult(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    return (res);
} 


/*
**  Operation div  vector xyz
**
**   a / b 
**  return -> vector xyz
*/

t_xyz   ft_xyz_div_doub(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    return (res);
}

/*
** Len  vector xyz
**
**  return -> Len xyz
*/

double ft_len_vect(t_xyz a)
{
    double len;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (len);
}

/*
**  Operation scalar mult  vector xyz 
**
**   <a , b >
**  return -> vector xyz
*/

double ft_xyz_mult_xyz(t_xyz a, t_xyz b)
{
    double res;

    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return (res);
}

/*
**  Create vect in 2 point 
**
**  b - a
**  return -> vector xyz
*/

t_xyz   ft_vect_two_point(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = b.x - a.x;
    res.y = b.y - a.y;
    res.z = b.z - a.z;
    return (res);
}

t_rgb   ft_rgb_mult_db(t_rgb rgb, double a)
{
    rgb.RED = (int)((double)rgb.RED * a);
    rgb.GREEN = (int)((double)rgb.GREEN * a);
    rgb.BLUE = (int)((double)rgb.BLUE * a);
    if (rgb.RED > 255)
        rgb.RED = 255;
    if (rgb.GREEN > 255)
        rgb.GREEN = 255;
    if (rgb.BLUE > 255)
        rgb.BLUE = 255;
    return (rgb);           
}

/*
**  the quadratic equation 
**  D = B^2 - 4 * A * C 
**  
**  return -> MINIMAL X OR INFINITY
*/

void  ft_quadrat_equat(double k1, double k2 , double k3 ,t_pixel *pixel,t_sphere *spher)
{
    double discr;
    double t1;
    double t2;

    discr = k2 * k2 - 4 * k1 * k3;
    if (discr < 0)
        return ;//(INFINITY);
    t1 = (-k2 + sqrt(discr)) / (2*k1);
    t2 = (-k2 - sqrt(discr)) / (2*k1);
    
    if ((t1 < t2) && (t1 < pixel->t) && (t1 > 0.0))
    {
        //printf("!!!!\n");
        pixel->rgb = spher->rgb;
        pixel->t = t1;
        pixel->spher_cor = spher->coord_sph_centr;
        //return (t1);
    }
    else if ((t2 <= t1) && (t2 < pixel->t) && (t2 > 0))
    {
       // printf("!!!!\n");
        pixel->rgb = spher->rgb;
        pixel->t = t2;
        pixel->spher_cor = spher->coord_sph_centr;
        //return (t2);
    }
    /*if (t1 < 0.0 && t2 > 0.0)
        return(t2);
    if (t2 < 0.0 && t1 > 0.0)
        return(t1);    
    if (t1 < t2)
        return (t1);
    return (t2);*/    
}

/*int     ft_fun_color()
{


}
*/

/*
**  Cicle for all pixel
**  
** Example:
** 600 600
*/

double mind(double a, double b)
{
    if (a < b)
        return (a);
    return(b);    
}


double  ft_compute_lighting(t_all_obj *all_obj,t_xyz p, t_xyz n)
{
    double i;
    double n_don_l;
    t_xyz l;
    t_list *light_all;
    t_light *li;   

    i = all_obj->al.light;
    //printf("p  x:%f y:%f z: %f\n",p.x,p.y,p.z);
    //printf("n  x:%f y:%f z: %f\n",n.x,n.y,n.z);
    light_all = all_obj->light;
    while(light_all)
    {
        li = light_all->content;
        l =  ft_xyz_minus(li->cord_l_point,p);
        n_don_l = ft_xyz_mult_xyz(n,l);
        if (n_don_l > 0.0)
        {
            i +=  li->light_brightness * n_don_l /( ft_len_vect(n) * ft_len_vect(l));
        }
        light_all = light_all->next;
    }    
    return (i);
}


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

/*
**  ft_ray_trace
**  
**  
**
**  return (int) color in pixel
*/


int     ft_ray_trace(t_all_obj *all_obj, double x, double y)
{
    t_xyz v;
    t_xyz o;
    t_xyz d;
    t_xyz c;
    t_list *sp;
    t_sphere *spher;
    t_xyz oc;

    t_xyz p;
    t_xyz n;
    
    double k1;
    double k2;
    double k3;
    double kf;

    sp = all_obj->sphere;
    o = ft_create_xyz(0.0,0.0,0.0);
    v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1.0);
    d = ft_xyz_minus(v,o);
                   
    t_pixel pixel;
    pixel.t = MAX_DB;
    pixel.rgb = all_obj->al.rgb;

    
    while (sp)
    {
                spher = sp->content;
                c.x =   spher->coord_sph_centr.x;
                c.y =   spher->coord_sph_centr.y;
                c.z =   spher->coord_sph_centr.z;

                oc = ft_xyz_minus(o,c);    
                k1 = ft_xyz_mult_xyz(d,d);
                k2 = 2 * ft_xyz_mult_xyz(oc,d);
                k3 = ft_xyz_mult_xyz(oc,oc) - pow(spher->diametr,2);

                ft_quadrat_equat(k1,k2,k3,&pixel,spher);

                sp = sp->next;
    }
    
    sp = all_obj->sphere;
    if (pixel.t == MAX_DB)
        return (create_rgb(pixel.rgb.RED,pixel.rgb.GREEN,pixel.rgb.BLUE));

    p = ft_xyz_plus(o,ft_xyz_mult(d,pixel.t));
    n = ft_xyz_minus(p,pixel.spher_cor);
    n = ft_xyz_div_doub(n,ft_len_vect(n));
    kf = ft_compute_lighting(all_obj,p,n);
    pixel.rgb = ft_rgb_mult_db(pixel.rgb,kf);
    return (create_rgb(pixel.rgb.RED,pixel.rgb.GREEN,pixel.rgb.BLUE));
}

int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    int cx;
    int cy;
    int color;

    double x;
    double y;

    cx = 0;
    cy = 0;
    while (cy < all_obj->reso.height)
    {
        while(cx < all_obj->reso.width)
        {
            //cx cy -> x y
            x = ft_convert_scr_to_dec_x(cx,all_obj->reso.width,-(all_obj->reso.width/2),all_obj->reso.width/2);
            y = ft_convert_scr_to_dec_y(cy,all_obj->reso.height,-(all_obj->reso.height/2),all_obj->reso.height/2);
            //printf("My x: %f  My y: %f\n",x,y);
            color = ft_ray_trace(all_obj,x,y);
            mlx_pixel_put(vars->mlx,vars->win,cx,cy,color);
            cx++;
        }
        cx = 0;
        cy++;
    }
    return (1);
}