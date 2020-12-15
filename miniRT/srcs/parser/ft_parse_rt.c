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

#define eps 1e-7
#define inf 1.0 / 0.0
/*
** perror-> write string and last error
** strerror(error) -> pointer in str with error  
*/


int             ft_check_normalizate(t_xyz xyz)
{
    if (xyz.x > 1.0 || xyz.x < -1.0 || xyz.y > 1.0 || xyz.y < -1.0
        || xyz.z > 1.0 || xyz.z < -1.0) 
        return(0);
    return (1);
}

int            ft_parse_R(t_all_obj *my,char *str)
{
    int width;
    int height;

    if ((*my).cnt.R > 1)
         ft_error(4);
    width = -1;
    height = -1;
    write(1,"FIND R\n",7);
    str++;
    width = ft_atoi(str);
    while (*str && (ft_isspace(*str)))
        str++;    
    while (*str && ft_isdigit(*str))
        str++;
    height = ft_atoi(str);
    my->reso.width = width;
    my->reso.height = height;
    my->cnt.R += 1;
    if (width <= 0 || height <= 0)
        ft_error(4);
    return (1);
}

int            ft_parse_A(t_all_obj *my,char *str)
{
    write(1,"FIND A\n",7);
    int i;

    i = 1;
    (*my).al.light = ft_atof(str + i);
    if (my->al.light ==  1.0 / 0.0 || my->al.light > 1.0 || my->al.light < 0.0)
        ft_error(5);
    ft_skip_atof(str, &i);    
    (*my).al.rgb = ft_atoirgb(str, &i);
    if (!(ft_check_rgb((*my).al.rgb)))
        ft_error(5);
    //printf("r:%d\n",my->al.rgb.RED);
    //printf("g:%d\n",my->al.rgb.GREEN);   
    //printf("b:%d\n",my->al.rgb.BLUE);    
    my->cnt.A+=1;    
    return (1);
}

int            ft_parse_c(t_all_obj *my,char *str)
{
    write(1,"FIND c\n",7);
    int i;
    
    i = 1;
    (*my).camera.coord_pointer = ft_atoi_xyz(str,&i);
    if ((*my).camera.coord_pointer.x == inf || (*my).camera.coord_pointer.y == inf
        || (*my).camera.coord_pointer.z == inf)
        ft_error(7);
    (*my).camera.normal_orientr_vec = ft_atoi_xyz(str,&i);
    if ((*my).camera.normal_orientr_vec.x == inf || (*my).camera.normal_orientr_vec.y == inf
        || (*my).camera.normal_orientr_vec.z == inf)
        ft_error(7);
    (*my).camera.FOV = ft_atof(str + i);
    if (((*my).camera.FOV < 0.0) || ((*my).camera.FOV) > 180.0)
        ft_error(7);
    return (1);
}

int           ft_parse_l(t_all_obj *my,char *str)
{
    write(1,"FIND l\n",7);
    int i;

    i = 1;
    (*my).light.cord_l_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz((*my).light.cord_l_point))
        ft_error(8);
    (*my).light.light_brightness = ft_atof(str + i);
    if ((*my).light.light_brightness > 1.0 || (*my).light.light_brightness < 0.0)
        ft_error(8);
    ft_skip_atof(str,&i);
    (*my).light.rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb((*my).light.rgb))
        ft_error(8);
    /*printf("s:%s\n",str + i);    
    printf("x:%f\n",(*my).light.cord_l_point.x);
    printf("y:%f\n",(*my).light.cord_l_point.y);
    printf("z:%f\n",(*my).light.cord_l_point.z);
    printf("lb:%f\n",(*my).light.light_brightness);
    printf("r:%d\n",(*my).light.rgb.RED);
    printf("g:%d\n",(*my).light.rgb.GREEN);
    printf("b:%d\n",(*my).light.rgb.BLUE);
    */
    return (1);
}


int           ft_parse_sp(t_all_obj *my,char *str)
{
    write(1,"FIND sp\n",8);
    (void) my;
    t_sphere *sp;
    t_list  *newel;
    int i;

    sp = malloc(sizeof(t_sphere));
    i = 2;
    sp->coord_sph_centr = ft_atoi_xyz(str, &i);
    if (!ft_check_xyz(sp->coord_sph_centr))
        ft_error(9);
    sp->diametr = ft_atof(str + i);
    if (sp->diametr == inf || sp->diametr < 0.0)
        ft_error(9);
    //printf("s1:%s\n",str + i);    
    ft_skip_atof(str,&i);
    //printf("s2:%s\n",str + i);
    sp->rgb = ft_atoirgb(str, &i);
    if (!ft_check_rgb(sp->rgb))
        ft_error(9);
    newel = ft_lstnew(sp);
    ft_lstadd_back(&my->sphere,newel);   
    //printf("x: %f\n",sp.coord_sph_centr.x);
    //printf("y: %f\n",sp.coord_sph_centr.y);
    //printf("z: %f\n",sp.coord_sph_centr.z);
    //printf("di: %f\n",sp->diametr);
    return(1);
}

int           ft_parse_cy(t_all_obj *my,char *str)
{
    (void) my;
    (void) str;
    int i;
    write(1,"FIND cy\n",8);
    t_cylinder *cy;

    i = 2;
    cy = malloc(sizeof(t_cylinder));
    cy->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord))
        ft_error(10);
    cy->normal_orientr_vec = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(cy->cord) || !ft_check_normalizate(cy->normal_orientr_vec))
        ft_error(10);
   
    cy->diameter = ft_atof(str + i);
    ft_skip_atof(str, &i);
    cy->height = ft_atof(str +i);
    ft_skip_atof(str, &i);
    if (cy->diameter < 0.0 || cy->height < 0.0)
        ft_error(10);
   cy->rgb = ft_atoirgb(str, &i);
   if (!ft_check_rgb(cy->rgb))
        ft_error(10);
    /*
    printf("x: %f\n",cy->cord.x);
    printf("y: %f\n",cy->cord.y);
    printf("z: %f\n",cy->cord.z);
    printf("x: %f\n",cy->normal_orientr_vec.x);
    printf("y: %f\n",cy->normal_orientr_vec.y);
    printf("z: %f\n",cy->normal_orientr_vec.z);
    printf("r: %d\n",cy->rgb.RED);
    printf("g: %d\n",cy->rgb.GREEN);
    printf("b: %d\n",cy->rgb.BLUE);
    printf("d: %f\n",cy->diameter);
    printf("h: %f\n",cy->height);
    */

    return (1);
}

int           ft_parse_pl(t_all_obj *my , char *str)
{
    write(1,"FIND pl\n",8);
    (void) str;
    (void) my;
    t_plane *pl;
    int i;
    
    i = 2;
    pl = malloc((sizeof(t_plane)));
    pl->cord = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(pl->cord))
        ft_error(10);
    pl->normal_orientr_vec = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(pl->cord) || !ft_check_normalizate(pl->normal_orientr_vec))
        ft_error(10);
    pl->rgb = ft_atoirgb(str, &i);

    /*printf("x: %f\n",pl->cord.x);
    printf("y: %f\n",pl->cord.y);
    printf("z: %f\n",pl->cord.z);
    printf("x: %f\n",pl->normal_orientr_vec.x);
    printf("y: %f\n",pl->normal_orientr_vec.y);
    printf("z: %f\n",pl->normal_orientr_vec.z);
    printf("r: %d\n",pl->rgb.RED);
    printf("g: %d\n",pl->rgb.GREEN);
    printf("b: %d\n",pl->rgb.BLUE);
    */

    return(1);
}

int           ft_parse_sq(t_all_obj *my , char *str)
{
     write(1,"FIND sq\n",8);
    (void) str;
    (void) my;
    t_square *sq;
    int i;

    sq = malloc(sizeof(t_square));
    i = 2;
    sq->cord_sq_cen= ft_atoi_xyz(str, &i);
    if (!ft_check_xyz(sq->cord_sq_cen))
        ft_error(11);
    sq->normal_orientr_vec = ft_atoi_xyz(str,&i);
    if (!ft_check_normalizate(sq->normal_orientr_vec))
        ft_error(11);
    sq->side = ft_atof(str + i);
    ft_skip_atof(str,&i);
    if (sq->side == inf)
        ft_error(11);
   sq->rgb = ft_atoirgb(str,&i);
   if (!(ft_check_rgb(sq->rgb)))
    ft_error(11); 
    /*
    printf("x: %f\n",sq->cord_sq_cen.x);
    printf("y: %f\n",sq->cord_sq_cen.y);
    printf("z: %f\n",sq->cord_sq_cen.z);
    printf("x: %f\n",sq->normal_orientr_vec.x);
    printf("y: %f\n",sq->normal_orientr_vec.y);
    printf("z: %f\n",sq->normal_orientr_vec.z);
    printf("r: %d\n",sq->rgb.RED);
    printf("g: %d\n",sq->rgb.GREEN);
    printf("b: %d\n",sq->rgb.BLUE);
    printf("side: %f\n",sq->side);
    */
    return(1);
}
int           ft_parse_tr(t_all_obj *my , char *str)
{
    write(1,"FIND tr\n",8);
    (void) str;
    (void) my;
    t_triangle *tr;
    int i;

    i = 2;
    tr = malloc(sizeof(t_triangle));
    tr->first_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->first_point))
        ft_error(12);
    tr->second_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->second_point))
        ft_error(12);
    tr->third_point = ft_atoi_xyz(str,&i);
    if (!ft_check_xyz(tr->third_point))
        ft_error(12);
    tr->rgb = ft_atoirgb(str,&i);
    if (!ft_check_rgb(tr->rgb))
        ft_error(12);
    /*printf("r: %d\n",tr->rgb.RED);
    printf("g: %d\n",tr->rgb.GREEN);
    printf("b: %d\n",tr->rgb.BLUE); */
    return (1);
}

int           ft_parse_str(char *str, t_all_obj *my)
{
    (void) my;
    int len;

    len = ft_strlen(str);

    if (ft_strnstr(str," ",1) || ft_strnstr(str,"\n",1))
        return (1);
    if (len < 5)
        ft_error(6);
    if (ft_strnstr(str,"R",1))
        return (ft_parse_R(my,str));    
    else if (ft_strnstr(str,"cy",2))
        return(ft_parse_cy(my,str));
    else if (ft_strnstr(str,"A",1))
        return (ft_parse_A(my,str));
    else if (ft_strnstr(str,"c",1))
        return(ft_parse_c(my,str));
    else if (ft_strnstr(str,"l",1))
        return(ft_parse_l(my,str));
    else if (ft_strnstr(str,"sp",2))
    {
        ft_parse_sp(my, str);
        //t_sphere *a;
        //a = my->sphere->content;
       // printf("di:%f\n",a->diametr);
    }
    else if (ft_strnstr(str,"pl",2))
        return (ft_parse_pl(my,str));
    else if (ft_strnstr(str,"sq",2))
       return (ft_parse_sq(my,str));
    else if (ft_strnstr(str,"tr",2))
        return (ft_parse_tr(my,str));
    return (1);        
}

void         ft_init_t_cnt_obj(t_cnt_object *my)
{
    my->R = 0;
    my->A = 0;
    my->c = 0;
    my->l = 0;
    my->sp = 0;
    my->pl = 0;
    my->sq = 0;
    my->cy = 0;
    my->tr = 0;
}
void        ft_init_t_all_obj(t_all_obj *my)
{
        ft_init_t_cnt_obj(&(my->cnt));
        (*my).reso.height = -1;
        (*my).reso.width = -1;

}

void        ft_parse_file_rt(int fd)
{
            char *str;
            t_all_obj my_rt;
            ft_init_t_all_obj(&my_rt);

            while ((get_next_line(fd,&str)) == 1)
            {
                printf("s:!%s!\n",str);
                if (!ft_parse_str(str,&my_rt))
                {
                    free(str);
                    exit(0); 
                }
                free(str);
            }
            if (str)
                 free(str);
}

int         ft_parse_rt(char *file)
{
    int fd;

    if ((fd = open(file,O_RDONLY)) > 0)
    {
        write(1,"OK\n",3);
        ft_parse_file_rt(fd);
    }
    else 
    {
        perror("Error\n");
        exit(0);
    }
    return (1);
}
