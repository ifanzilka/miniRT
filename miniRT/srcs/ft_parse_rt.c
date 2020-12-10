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

/*
** perror-> write string and last error
** strerror(error) -> pointer in str with error  
*/

int           ft_parse_str(char *str, t_all_obj *my)
{
    (void) my;
    int len;

    len = ft_strlen(str);
    if (len < 5)
        return (0);
    if (ft_strnstr(str,"R",1))
        write(1,"FIND R\n",7);
    else if (ft_strnstr(str,"cy",2))
        write(1,"FIND cy\n",8);    
    else if (ft_strnstr(str,"A",1))
        write(1,"FIND A\n",7);
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
    else if (ft_strnstr(str," ",2) || ft_strnstr(str,"\n",1))
        return (1);
    return (0);        
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
