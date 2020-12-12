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
#define eps 1e-7
/*
** perror-> write string and last error
** strerror(error) -> pointer in str with error  
*/

int            ft_parse_R(t_all_obj *my,char *str)
{
    int width;
    int height;

    width = -1;
    height = -1;
    write(1,"FIND R\n",7);
    str++;
    width = ft_atoi(str);
    while (*str && (*str == ' '))
        str++;    
    while (*str && ft_isdigit(*str))
        str++;    
    printf("s: %s\n",str);    
    height = ft_atoi(str);    
    printf("w: %d\n",width);
    printf("h: %d\n",height);
    my->reso.width = width;
    my->reso.height = height;
    my->cnt.R += 1;
    if (width <= 0 || height <= 0)
        return (0);
    return (1);
}

int            ft_parse_A(t_all_obj *my,char *str)
{
    write(1,"FIND A\n",7);
    str++;
    my->al.light = ft_atoi_double(str);
    if (fabs(my->al.light + 1.0 ) < eps)
        return (0);

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
        return (0);
    if (ft_strnstr(str,"R",1))
        return (ft_parse_R(my,str));    
    else if (ft_strnstr(str,"cy",2))
        write(1,"FIND cy\n",8);    
    else if (ft_strnstr(str,"A",1))
        return (ft_parse_A(my,str));
    else if (ft_strnstr(str,"c",1))
        write(1,"FIND c\n",7);
    else if (ft_strnstr(str,"l",1))
        write(1,"FIND l\n",7);
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
