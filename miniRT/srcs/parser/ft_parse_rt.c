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


t_l_list * ft_l_lsnew(void  *content)  // а- значение первого узла
{
  t_l_list *lst;

  lst = (t_l_list*)malloc(sizeof(t_l_list));
  if (!lst)
    return (NULL);
  lst->content = content;
  lst->next = NULL; 
  lst->prev = NULL; 
  return(lst);
}

void	ft_l_lstadd_front(t_l_list **lst,   t_l_list *new)
{   
    t_l_list *tmp;

	if (!lst || !new)
		return ;    
    tmp = *lst; 
    if (!(tmp))
        *lst = new;
    else 
    {       
	    new->next = *lst;
        new->prev = tmp->prev;
        tmp->prev = new;
	    *lst = new;
    }    
}


void	ft_l_lstadd_back(t_l_list **lst,   t_l_list *new)
{   
    t_l_list *tmp;
	if (!lst || !new)
		return ;
    tmp = *lst;
    if (!tmp)
    {
        printf("ok\n");
        *lst = new;
    }
    else
    {    
        while (tmp->next)
			tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }    
}



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
    //if (len < 5)
    //    ft_error(6);
    if (ft_strnstr(str,"R",1))
        return (ft_parse_R(my,str));    
    else if (ft_strnstr(str,"cy",2))
        return(ft_parse_cy(my,str));
    else if (ft_strnstr(str,"A",1))
        return (ft_parse_A(my,str));
    else if (ft_strnstr(str,"c",1))
        return(ft_parse_c(my,str));
    else if (ft_strnstr(str,"l",1))
        ft_parse_l(my,str);
    else if (ft_strnstr(str,"sp",2))
    {
        ft_parse_sp(my, str);
        //t_sphere *a;
        //a = my->sphere->content;
        //printf("di:%f\n",a->diametr);
    }
    else if (ft_strnstr(str,"pl",2))
        return (ft_parse_pl(my,str));
    else if (ft_strnstr(str,"sq",2))
       return (ft_parse_sq(my,str));
    else if (ft_strnstr(str,"tr",2)) 
        return (ft_parse_tr(my,str));
    else if (ft_strnstr(str,"\n",2))
        return (1);
    else if (ft_strnstr(str," ",2))
        return (1);
    else if (ft_strnstr(str,"#",1))
        return (1);
    else if (ft_strlen(str) == 0)
        return (1);             
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
        //(*my).light = NULL;
        //(*my).sphere = NULL;
        //(*my).sphere = malloc(sizeof(t_list));
        //(*my).light= malloc(sizeof(t_list));
}

void        ft_parse_file_rt(int fd)
{
            char *str;
            t_all_obj *my_rt;
            int gnl;

            my_rt = malloc(sizeof(t_all_obj));
            if (!my_rt)
                ft_error(14);
            ft_init_t_all_obj(my_rt);
            gnl = 1;
            while ( gnl != 0 && ( gnl = get_next_line(fd,&str)) >= 0)
            {
                printf("s:!%s!\n",str);
                if (!ft_parse_str(str,my_rt))
                {
                    //ft_free_struct(); (если что то уже добавили в структуры ндо очистить бдует)
                    free(str);
                    exit(0); 
                }

                free(str);
            }
             printf("!\n");
            t_camera *cam;
            cam = (t_camera *)(my_rt->ll_camera->content);
            printf("!!\n");
            my_rt->camera = cam;
            printf("cam : x %f y %f z%f \n", my_rt->camera->coord_pointer.x,my_rt->camera->coord_pointer.y,my_rt->camera->coord_pointer.z);
            
            t_list  *tmp;
            t_light *tmp_l;
            tmp = my_rt->l_light;
            while (tmp)
            {
                tmp_l = tmp->content;
                printf("%f BRIGHTNESS\n", tmp_l->light_brightness);
                tmp = tmp->next;
            }

            t_list  *tmps;
            t_sphere *tmps_sp;
            tmps = my_rt->l_sphere;
            while (tmps)
            {
                tmps_sp = tmps->content;
                printf("%f SPHERE\n", tmps_sp->diametr);
                tmps = tmps->next;
            }

            t_list  *tmppl;
            t_plane *tmps_pl;
            tmppl = my_rt->l_pl;
            while (tmppl)
            {
                tmps_pl = tmppl->content;
                printf("%d pl\n", tmps_pl->rgb.red);
                tmppl = tmppl->next;
            }

            t_list  *tmptr;
            t_triangle *tmps_tr;
            tmptr = my_rt->l_tr;
            while (tmptr)
            {
                tmps_tr = tmptr->content;
                printf("%d tr\n", tmps_tr->rgb.red);
                tmptr = tmptr->next;
            }

            ft_init_disp(my_rt);
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
