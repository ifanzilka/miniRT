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
    //x = (cx * xsize) / (width);
    return (x);
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
    y = ymin + (cy / h) * ysize;
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

int     cicle_for_pixel(t_all_obj *all_obj,t_vars *vars)
{
    int cx;
    int cy;
    int color;
    t_xyz v;
    t_xyz o;
    
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
           // printf("My x: %f\nMy y: %f",x,y);

            
            //fun_color(D,Camera,0.00001,INFINITY,t_struct)
            v = ft_create_v(x,y,all_obj->reso.width,all_obj->reso.height, 1.0);
            color = create_rgb(255,0,255);
            mlx_pixel_put(vars->mlx,vars->win,cx,cy,color);
            
            //mlx_pixel_put();
            //pixel_put
            cx++;
        }
        cx = 0;
        cy++;
    }
    return (1);
}