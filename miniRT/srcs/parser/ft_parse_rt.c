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
    else
        ft_error(6);    
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
                //printf("s:!%s!\n",str);
                if (!ft_parse_str(str,&my_rt))
                {
                    //ft_free_struct(); (если что то уже добавили в структуры ндо очистить бдует)
                    free(str);
                    exit(0); 
                }

                free(str);
            }
            ft_init_disp(&my_rt);
            //ft_check_t_all_obj(); (проверяю на валидность данные)
            if (str)
                 free(str);


}

int         ft_parse_rt(char *file)
{
    int fd;

    if ((fd = open(file,O_RDONLY)) > 0)
    {
        //write(1,"OK\n",3);
        ft_parse_file_rt(fd);
    }
    else 
    {
        perror("Error\n");
        exit(0);
    }
    return (1);
}
