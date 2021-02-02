/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:54:36 by bmarilli          #+#    #+#             */
/*   Updated: 2020/12/10 20:54:55 by bmarilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minirt.h>
#include <parse.h>
#include <ray_tracing.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define eps 1e-7

/*
** perror-> write string and last error
** strerror(error) -> pointer in str with error  
*/

void ft_parse_str(char *str, t_rt *rt)
{
    if (ft_strnstr(str, " ", 1) || ft_strnstr(str, "\n", 1))
        return;
    if (ft_strnstr(str, "R", 1))
        ft_parse_r(rt, str);
    else if (ft_strnstr(str, "cy", 2))
        ft_parse_cy(rt, str);
    else if (ft_strnstr(str, "A", 1))
        ft_parse_a(rt, str);
    else if (ft_strnstr(str, "c", 1))
        ft_parse_c(rt, str);
    else if (ft_strnstr(str, "l", 1))
        ft_parse_l(rt, str);
    else if (ft_strnstr(str, "sp", 2))
        ft_parse_sp(rt, str);
    else if (ft_strnstr(str, "pl", 2))
        ft_parse_pl(rt, str);
    else if (ft_strnstr(str, "sq", 2))
        ft_parse_sq(rt, str);
    else if (ft_strnstr(str, "tr", 2))
        ft_parse_tr(rt, str);
    else if (ft_strnstr(str, "#", 1) || ft_strlen(str) == 0)
        return;
}
void ft_init_t_rt(t_rt *rt)
{
    rt->reso.height = -1;
    rt->reso.width = -1;
    rt->cnt.r = 0;
    rt->cnt.a = 0;
    rt->cnt.c = 0;
    rt->cnt.l = 0;
    rt->cnt.sp = 0;
    rt->cnt.pl = 0;
    rt->cnt.sq = 0;
    rt->cnt.cy = 0;
    rt->cnt.tr = 0;
    rt->camera = NULL;
    rt->ll_camera = NULL;
    rt->l_sphere = NULL;
    rt->l_light = NULL;
    rt->l_pl = NULL;
    rt->l_tr = NULL;
    rt->l_sq = NULL;
    rt->l_cy = NULL;
    rt->l_p = NULL;
}

int ft_check_t_rt(t_rt *rt)
{
    if (rt->cnt.r < 1|| rt->cnt.c < 1 || rt->cnt.a < 1)
        return(1);
    else if (ft_lstsize(rt->l_light) != rt->cnt.l)
        return(1);
    else if (ft_l_lstsize(rt->ll_camera) != rt->cnt.c)
        return(1);
    else if (ft_lstsize(rt->l_cy) != rt->cnt.cy)
        return(1);
    else if (ft_lstsize(rt->l_pl) != rt->cnt.pl)
        return(1);
    else if (ft_lstsize(rt->l_sphere) != rt->cnt.sp)
        return(1);
    else if (ft_lstsize(rt->l_sq) != rt->cnt.sq)
        return(1);
    else if (ft_lstsize(rt->l_tr) != rt->cnt.tr)
        return(1);                        
    return (0);
}

/*
**void    fun_li(void *li)
**{
**    t_light *p;
**    p = (t_light *)li;
**    printf("li BRIGHTNESS %f \n",p->light_brightness);
**}
**
**void    fun_sp(void *li)
**{
**    t_sphere *p;
**    p = (t_sphere *)li;
**    printf("sp radius : %f \n",p->diametr);
**}
**
**void    fun_pl(void *li)
**{
**    t_plane *p;
**    p = (t_plane *)li;
**    printf("pl R : %d \n",p->rgb.red);
**}
**void    fun_tr(void *li)
**{
**    t_triangle *p;
**    p = (t_triangle *)li;
**    printf("tr red : %d \n",p->rgb.red);
**}
**
**void    fun_cam(void *c)
**{
**    t_camera *p;
**    p = (t_camera *)c;
**   printf("cam : x %f y %f z%f \n", p->coord_pointer.x,p->coord_pointer.y,p->coord_pointer.z);
**}
**
**void del_pl(void *pl)
**{
**    t_plane *p;
**    p = (t_plane *)pl;
**    free(pl);
**}
**    ft_l_lstiter(rt->ll_camera,fun_cam);
**    ft_lstiter(rt->l_light, fun_li);
**    ft_lstiter(rt->l_sphere, fun_sp);
**    ft_lstiter(rt->l_pl, fun_pl);
**    ft_lstiter(rt->l_tr, fun_tr);
*/

void ft_parse_file_rt(int fd, int argc)
{
    t_rt *rt;
    char    *str;
    int     gnl;

    if (!(rt = malloc(sizeof(t_rt))))
        ft_error(err_malloc);
    ft_init_t_rt(rt);
    gnl = 1;
    while (gnl != 0 && (gnl = get_next_line(fd, &str)) >= 0)
    {
        ft_parse_str(str, rt);
        free(str);
    }
    if (gnl == -1)
        ft_error_rt(err_rt,rt); 
    if ((ft_check_t_rt(rt)))
        ft_error_rt(err_rt,rt);    
    rt->camera = (t_camera *)(rt->ll_camera->content);
    if (argc == 2)
        ft_init_disp(rt);
    else if (argc == 3)
        ft_init_img(rt);
    ft_clear_rt(rt);
}

int ft_parse_rt(char *file, int argc)
{
    int fd;

    if ((fd = open(file, O_RDONLY)) > 0)
        ft_parse_file_rt(fd, argc);
    else
    {
        perror("Error\n");
        exit(0);
    }
    return (1);
}
