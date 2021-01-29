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

int             ft_check_normalizate(t_xyz xyz)
{
    if (xyz.x > 1.0 || xyz.x < -1.0 || xyz.y > 1.0 || xyz.y < -1.0
        || xyz.z > 1.0 || xyz.z < -1.0) 
        return(0);
    if (xyz.x + xyz.y + xyz.z < 0.0001 && xyz.x + xyz.y + xyz.z > -0.0001)
        return(0);    
    return (1);
}

void           ft_parse_str(char *str, t_rt *rt)
{   
    if (ft_strnstr(str," ",1) || ft_strnstr(str,"\n",1))
        return ;
    if (ft_strnstr(str,"R",1))
        ft_parse_R(rt,str);    
    else if (ft_strnstr(str,"cy",2))
        ft_parse_cy(rt,str);
    else if (ft_strnstr(str,"A",1))
        ft_parse_A(rt,str);
    else if (ft_strnstr(str,"c",1))
        ft_parse_c(rt,str);
    else if (ft_strnstr(str,"l",1))
        ft_parse_l(rt,str);
    else if (ft_strnstr(str,"sp",2))
        ft_parse_sp(rt, str);
    else if (ft_strnstr(str,"pl",2))
        ft_parse_pl(rt,str);
    else if (ft_strnstr(str,"sq",2))
        ft_parse_sq(rt,str);
    else if (ft_strnstr(str,"tr",2)) 
        ft_parse_tr(rt,str);
    else if (ft_strnstr(str,"#",1) || ft_strlen(str) == 0)
        return ;         
}
void        ft_init_t_rt(t_rt *rt)
{
    rt->reso.height = -1;
    rt->reso.width = -1;
    rt->cnt.R = 0;
    rt->cnt.A = 0;
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

// void    fun_li(void *li)
// {
//     t_light *p;
//     p = (t_light *)li;
//     printf("li BRIGHTNESS %f \n",p->light_brightness);
// }

// void    fun_sp(void *li)
// {
//     t_sphere *p;
//     p = (t_sphere *)li;
//     printf("sp radius : %f \n",p->diametr);
// }

// void    fun_pl(void *li)
// {
//     t_plane *p;
//     p = (t_plane *)li;
//     printf("pl R : %d \n",p->rgb.red);
// }
// void    fun_tr(void *li)
// {
//     t_triangle *p;
//     p = (t_triangle *)li;
//     printf("tr red : %d \n",p->rgb.red);
// }

// void    fun_cam(void *c)
// {
//     t_camera *p;
//     p = (t_camera *)c;
//    printf("cam : x %f y %f z%f \n", p->coord_pointer.x,p->coord_pointer.y,p->coord_pointer.z);
// }

// void del_pl(void *pl)
// {
//     t_plane *p;
//     p = (t_plane *)pl;
//     free(pl);
// }
// static void	init(t_all *all)
// {
// 	my_mlx_init(all);
// 	if (!(rt->reso.win = mlx_new_window(rt->reso.mlx, rt->reso.width,
// 	rt->reso.height, "cub3D")))
// 		error_handler(MAP_PARS, 0);
// 	my_image_init(all);
// 	my_plr_init(all);
// 	sprites_init(all);
// 	read_text(all);
// 	draw_all0(all);
// }
// void		create_file_header(t_all *all, int fd)
// {
// 	unsigned char	*file_header;
// 	int				i;
// 	int				file_size;
// 	file_header = (unsigned char *)malloc(14 * sizeof(unsigned char));
// 	i = 0;
// 	while (i < 14)
// 	{
// 		file_header[i] = (unsigned char)(0);
// 		i++;
// 	}
// 	file_size = 14 + 40 + (4 * rt->reso.width * rt->reso.height);
// 	file_header[0] = (unsigned char)('B');
// 	file_header[1] = (unsigned char)('M');
// 	file_header[2] = (unsigned char)(file_size % 256);
// 	file_header[3] = (unsigned char)(file_size / 256 % 256);
// 	file_header[4] = (unsigned char)(file_size / 256 / 256 % 256);
// 	file_header[5] = (unsigned char)(file_size / 256 / 256 / 256);
// 	file_header[10] = (unsigned char)(14 + 40);
// 	write(fd, file_header, 14);
// 	free(file_header);
// }
// void		create_info_header(t_all *all, int fd)
// {
// 	int				i;
// 	unsigned char	*file_header;
// 	i = 0;
// 	file_header = (unsigned char *)malloc(40 * sizeof(unsigned char));
// 	while (i < 40)
// 	{
// 		file_header[i] = (unsigned char)(0);
// 		i++;
// 	}
// 	file_header[0] = (unsigned char)(40);
// 	file_header[4] = (unsigned char)(rt->reso.width % 256);
// 	file_header[5] = (unsigned char)(rt->reso.width / 256 % 256);
// 	file_header[6] = (unsigned char)(rt->reso.width / 256 / 256 % 256);
// 	file_header[7] = (unsigned char)(rt->reso.width / 256 / 256 / 256);
// 	file_header[8] = (unsigned char)(rt->reso.height % 256);
// 	file_header[9] = (unsigned char)(rt->reso.height / 256 % 256);
// 	file_header[10] = (unsigned char)(rt->reso.height / 256 / 256 % 256);
// 	file_header[11] = (unsigned char)(rt->reso.height / 256 / 256 / 256);
// 	file_header[12] = (unsigned char)(1);
// 	file_header[14] = (unsigned char)(32);
// 	write(fd, file_header, 40);
// 	free(file_header);
// }
// void		create_image_to_file(t_all *all)
// {
// 	int y;
// 	int line_length;
// 	line_length = rt->reso.width * all->img->bits_per_pixel / 8;
// 	y = rt->reso.height;
// 	while (0 <= y)
// 	{
// 		write(all->fd, (unsigned char *)(all->img->addr +
// 		y * all->img->line_length), line_length);
// 		y--;
// 	}
// }
// void		screen_save(t_all *all)
// {
// 	all->fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655);
// 	init(all);
// 	create_file_header(all, all->fd);
// 	create_info_header(all, all->fd);
// 	create_image_to_file(all);
// 	close(all->fd);
// 	write(1, "Image generate!\n", 17);
// 	my_exit();
// }




void        ft_parse_file_rt(int fd, int argc, char *file)
{
    t_rt *rt;
    char    *str;
    (void)  file;
    int gnl;
    
    if (!(rt = malloc(sizeof(t_rt))))
        ft_error(err_malloc);
    ft_init_t_rt(rt);
    gnl = 1;
    while ( gnl != 0 && ( gnl = get_next_line(fd,&str)) >= 0)
    {
        printf("s:!%s!\n",str);
        ft_parse_str(str,rt);
        free(str);
    }
    if (gnl == -1)
        ft_error(err_rt);
    //ft_check_t_rt(); (проверяю на валидность данные)    
    rt->camera = (t_camera *)(rt->ll_camera->content);
            
            //ft_l_lstiter(rt->ll_camera,fun_cam);
            // ft_lstiter(rt->l_light, fun_li);
            // ft_lstiter(rt->l_sphere, fun_sp);
            // ft_lstiter(rt->l_pl, fun_pl);
            // ft_lstiter(rt->l_tr, fun_tr);

    printf("l size %d \n",ft_lstsize(rt->l_pl));
            //void				ft_lstclear(t_list **lst, void (*del)(void*));
            //ft_lstclear(&rt->l_pl,del_pl);

            //ft_lstiter(t_list *lst, void (*f)(void *));
        //ft_error_rt(1,rt);       
     if (argc == 2)
        ft_init_disp(rt);
    else if (argc == 3)
        ft_init_img(rt);
    ft_clear_rt(rt);    
        //ft_create_bmp(rt);   
            
}

int         ft_parse_rt(char *file, int argc)
{
    int fd;

    if ((fd = open(file,O_RDONLY)) > 0)
        ft_parse_file_rt(fd,argc,file);
    else 
    {
        perror("Error\n");
        exit(0);
    }
    return (1);
}
