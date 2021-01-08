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

int     cicle(t_all_obj *all_obj,t_vars *vars)
{
    int x;
    int y;
    int color;

    x = 0;
    y = 0;
    while (y < all_obj->reso.height)
    {
        while(x < all_obj->reso.width)
        {
            color = create_rgb(255,0,0);
            mlx_pixel_put(vars->mlx,vars->win,x,y,color);
            //mlx_pixel_put();
            //pixel_put
            x++;
        }
        x = 0;
        y++;
    }
    return (1);
}