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
    while (ft_isspace(str[i]) || ft_isdigit(str[i]))
        i++;
    if (str[i] != '.' || !(i++))
        ft_error(5);
    while (ft_isdigit(str[i]))
        i++;
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
    if ((*my).light.cord_l_point.x == inf || (*my).light.cord_l_point.y == inf
        || (*my).light.cord_l_point.z == inf)
        ft_error(8);
    (*my).light.light_brightness = ft_atof(str + i);
    if ((*my).light.light_brightness > 1.0 || (*my).light.light_brightness < 0.0)
        ft_error(8);
    while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
    while (str[i] && ft_isdigit(str[i]))
		i++;
    if ((str[i] && str[i] == '.'))
    {
        i++;
        while (str[i] && ft_isdigit(str[i]))
		    i++;
    }
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
        write(1,"FIND cy\n",8);    
    else if (ft_strnstr(str,"A",1))
        return (ft_parse_A(my,str));
    else if (ft_strnstr(str,"c",1))
        return(ft_parse_c(my,str));
    else if (ft_strnstr(str,"l",1))
        return(ft_parse_l(my,str));
    else if (ft_strnstr(str,"sp",2))
        write(1,"FIND sp\n",8);
    else if (ft_strnstr(str,"pl",2))
        write(1,"FIND pl\n",8);
    else if (ft_strnstr(str,"sq",2))
        write(1,"FIND sq\n",8);
    else if (ft_strnstr(str,"tr",2))
        write(1,"FIND tr\n",8);
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
