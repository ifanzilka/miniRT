#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include "mlx.h"

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

int		create_rgb( int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

/*
** 0xFF -> all bits (1)
*/

int		get_r(int rgb)
{
	return (rgb & (0xFF << 16));
}

int		get_g(int rgb)
{
	return (rgb & (0xFF << 8));
}

int		get_b(int rgb)
{
	return (rgb & 0xFF);
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

t_xyz      ft_create_v(double x, double y, int width, int height, double z)
{
    t_xyz v;

    v.x = x / width;
    v.y = y / height;
    v.z = z;
    return (v);
}

t_xyz      ft_create_xyz(double x, double y,double z)
{
    t_xyz o;

    o.x = x;
    o.y = y;
    o.z = z;
    return (o);
}

t_xyz   ft_xyz_minus(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

t_xyz   ft_xyz_plus(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return (res);
}

t_xyz   ft_xyz_mult(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    return (res);
} 

t_xyz   ft_xyz_div_doub(t_xyz a, double b)
{
    t_xyz res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    return (res);
}

double ft_len_vect(t_xyz a)
{
    double len;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (len);
}

double ft_xyz_div_xyz(t_xyz a, t_xyz b)
{
    double res;

    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return (res);
}

t_xyz   ft_vect_two_point(t_xyz a, t_xyz b)
{
    t_xyz res;

    res.x = b.x - a.x;
    res.y = b.y - a.y;
    res.z = b.z - a.z;
    return (res);
}

double  ft_quadrat_equat(double k1, double k2 , double k3)
{
    double discr;
    double t1;
    double t2;

    discr = k2 * k2 - 4 * k1 * k3;
    if (discr < 0)
        return(INFINITY);
    t1 = (-k2 + sqrt(discr)) / (2*k1);
    t2 = (-k2 - sqrt(discr)) / (2*k1);
    if (t1 < t2)
        return (t1);
    return (t2);    
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

int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    int cx;
    int cy;
    int color;
    t_xyz v;
    t_xyz o;
    t_xyz d;
    t_xyz oc;
    t_xyz c;

    double x;
    double y;

    double k1;
    double k2;
    double k3;
    double t;
    //double t2;

    t_list *sp;

    sp = all_obj->sphere;
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

            
            //fun_color(D,Camera,0.00001,INFINITY,t_struct)




            v = ft_create_v(x, y, all_obj->reso.width, all_obj->reso.height, 1.0);
            o = ft_create_xyz(0.0,0.0,0.0);
            d = ft_xyz_minus(v,o);
            
            t = INFINITY;
            //color = create_rgb(255,255,255);
            while (sp)
            {
                t_sphere *spher;
                spher = sp->content;

                c.x =   spher->coord_sph_centr.x;
                c.y =   spher->coord_sph_centr.y;
                c.z =   spher->coord_sph_centr.z;

                //printf("x: %f\n",c.x);
                //printf("y: %f\n",c.y );
                //printf("z: %f\n", c.z); 
                oc = ft_xyz_minus(c,o);    
                k1 = ft_xyz_div_xyz(d,d);
                k2 = 2 * ft_xyz_div_xyz(oc,d);
                k3 = ft_xyz_div_xyz(oc,oc) - pow(spher->diametr,2);

                //printf("K1: %f\n",k1);
                //printf("K2: %f\n",k2);
                //printf("K3: %f\n",k3);

                if (t > ft_quadrat_equat(k1,k2,k3))
                {
                    t = ft_quadrat_equat(k1,k2,k3);
                    color = create_rgb(spher->rgb.RED,spher->rgb.GREEN,spher->rgb.BLUE);
                }
                
                if (t == INFINITY )//&& t < t_prev)
                {
                    //color = color;//create_rgb(spher->rgb.RED,spher->rgb.GREEN,spher->rgb.BLUE);
                    //printf("1!\n");
                    color = create_rgb(255,255,255);
                }
               // else 
                //{
                  //   color = create_rgb(255,255,255);
                    //printf("3!\n");
                    
                //}
                mlx_pixel_put(vars->mlx,vars->win,cx,cy,color);
                sp = sp->next;
                
            }
            sp = all_obj->sphere;
            //mlx_pixel_put();
            //pixel_put
            cx++;
        }
        cx = 0;
        cy++;
    }
    return (1);
}