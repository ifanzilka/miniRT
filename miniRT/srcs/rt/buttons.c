#include <ft_minirt.h>
#include "ray_tracing.h"

void    ft_next_cam(t_vars *vars)
{
    t_l_list    *ll_cam;
    t_all_obj   *rt;

    ft_putstr_fd("Next camera!\n",1);
    rt = vars->rt;
    ll_cam = rt->ll_camera;
    if (ll_cam->next == NULL)
        ft_putstr_fd("Camera in last!\n",1);
    else
    {
        rt->camera = (t_camera *)ll_cam->next->content;
        rt->ll_camera = rt->ll_camera->next;
        mlx_clear_window(vars->mlx, vars->win);
        cicle_for_pixel(vars->rt,vars);
    }
}

 void    ft_prev_cam(t_vars *vars)
 {
    t_l_list    *ll_cam;
    t_all_obj   *rt;

    ft_putstr_fd("Prev camera!\n",1);
    rt = vars->rt;
    ll_cam = rt->ll_camera;
    if (ll_cam->prev == NULL)
        ft_putstr_fd("Camera in first!\n",1);
    else
    {
        rt->camera = (t_camera *)ll_cam->prev->content;
        rt->ll_camera = rt->ll_camera->prev;
        mlx_clear_window(vars->mlx, vars->win);
        cicle_for_pixel(vars->rt,vars);
    }
 }

 void    ft_plus_cam(t_vars *vars)
 {
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.x *= -1;
    dir.y *= -1;
    cam->coord_pointer = ft_xyz_plus(cam->coord_pointer,ft_xyz_mult_db(dir,0.5));
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
  void    ft_minus_cam(t_vars *vars)
 {
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;

    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.x *= -1;
    dir.y *= -1;
    cam->coord_pointer = ft_xyz_minus(cam->coord_pointer,ft_xyz_mult_db(dir,0.5));
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
void    ft_right_cam(t_vars *vars)
{
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.x -= 0.2;
    dir = ft_xyz_normalaze(dir);
    //dir.x *= -1;
    //dir.y *= -1;
    cam->camera_direction =dir;
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
 void    ft_left_cam(t_vars *vars)
{
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.x += 0.2;
    dir = ft_xyz_normalaze(dir);
    cam->camera_direction =dir;
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }

 void    ft_up_cam(t_vars *vars)
{
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.y -= 0.2;
    dir = ft_xyz_normalaze(dir);
    //dir.x *= -1;
    //dir.y *= -1;
    cam->camera_direction =dir;
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
  void    ft_down_cam(t_vars *vars)
{
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.y += 0.2;
    dir = ft_xyz_normalaze(dir);
    //dir.x *= -1;
    //dir.y *= -1;
    cam->camera_direction =dir;
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
void    ft_revers_cam(t_vars *vars)
{
    t_all_obj   *rt;
    t_camera    *cam;
    t_xyz dir;
    
    rt = vars->rt;
    cam = rt->camera;
    dir = cam->camera_direction;
    dir.z *= -1.0;
    dir = ft_xyz_normalaze(dir);
    //dir.x *= -1;
    //dir.y *= -1;
    cam->camera_direction =dir;
    mlx_clear_window(vars->mlx, vars->win);
    cicle_for_pixel(vars->rt,vars);
 }
void    ft_plus_al(t_vars *vars)
{
    t_all_obj               *rt;
    t_ambient_lightning    *al;
    
    rt = vars->rt;
    al = &(rt->al);
    if (al->light + 0.05 < 1.0)
    {
        al->light += 0.05;
        mlx_clear_window(vars->mlx, vars->win);
        cicle_for_pixel(vars->rt,vars);
    }
 }
 void    ft_minus_al(t_vars *vars)
{
    t_all_obj               *rt;
    t_ambient_lightning    *al;
    
    rt = vars->rt;
    al = &(rt->al);
    if (al->light - 0.05 > 0.0)
    {
        al->light -= 0.05;
        mlx_clear_window(vars->mlx, vars->win);
        cicle_for_pixel(vars->rt,vars);
    }
 }