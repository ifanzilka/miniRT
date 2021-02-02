# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 23:36:03 by bmarilli          #+#    #+#              #
#    Updated: 2020/12/11 18:39:20 by bmarilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= gcc

AR		= ar rc 

DIR		= ./SRC/

HEADER	= ./includes

FLAGS	= -Wall -Wextra -Werror 

DIR_MEMORY = ./SRC/memory/

SRCS	= $(DIR)ft_bzero.c 		$(DIR)ft_isalnum.c 	$(DIR)ft_calloc.c \
		  $(DIR)ft_isascii.c  	$(DIR)ft_isdigit.c 	$(DIR)ft_isalpha.c \
		  $(DIR)ft_atoi.c 		$(DIR)ft_isprint.c 	$(DIR)ft_isspace.c\
		  $(DIR)ft_memcmp.c \
		  $(DIR)ft_memset.c  	$(DIR)ft_memchr.c 	$(DIR)ft_tolower.c \
		  $(DIR)ft_memcpy.c  	$(DIR)ft_strlen.c 	$(DIR)ft_memccpy.c \
		  $(DIR)ft_strchr.c  	$(DIR)ft_strdup.c  	$(DIR)ft_memmove.c \
		  $(DIR)ft_toupper.c  	$(DIR)ft_strlcat.c  $(DIR)ft_strlcpy.c \
		  $(DIR)ft_strnstr.c 	$(DIR)ft_strrchr.c  $(DIR)ft_strncmp.c \
		  $(DIR)ft_substr.c 	$(DIR)ft_strjoin.c 	$(DIR)ft_strtrim.c \
		  $(DIR)ft_split.c 		$(DIR)ft_itoa.c 	$(DIR)ft_strmapi.c \
		  $(DIR)ft_putchar_fd.c $(DIR)ft_putstr_fd.c $(DIR)ft_putendl_fd.c \
		  $(DIR)ft_putnbr_fd.c 	$(DIR)ft_intlen.c	$(DIR)ft_pow.c\
		  $(DIR)ft_print_n_char.c $(DIR)ft_memdel.c $(DIR)ft_memalloc.c\
		  $(DIR)ft_strnew.c		$(DIR)ft_itoa_with_zero.c\
		  $(DIR)ft_itoa_unsig_base.c 				$(DIR)ft_strdel.c\
		  $(DIR)ft_create_str.c $(DIR)ft_add_forward.c\
		  $(DIR)ft_add_back.c	$(DIR)ft_itoa_ll.c\
		  $(DIR)ft_atof.c\
		  $(DIR)ft_itoa_unsigned_ll.c $(DIR)ft_itoa_base_x.c \
		  $(DIR)ft_lstnew.c		$(DIR)ft_lstadd_front.c $(DIR)ft_lstsize.c \
		  $(DIR)ft_lstlast.c		$(DIR)ft_lstadd_back.c\
		  $(DIR)ft_l_lsnew.c	$(DIR)ft_l_lstadd_front.c	$(DIR)ft_l_lstadd_back.c\
		  $(DIR)ft_l_lstclear.c	$(DIR)ft_l_lstdelone.c	$(DIR)ft_l_lstiter.c\
		  $(DIR)ft_l_lstlast.c $(DIR)ft_l_lstsize.c\
		  $(DIR)ft_lstiter.c 	$(DIR)ft_lstclear.c\
		  $(DIR)ft_lst_cr_front.c \
		  $(DIR)ft_l_lst_cr_back.c $(DIR)ft_l_lst_cr_front.c \
		  $(DIR)ft_lstdelel.c \
		  $(DIR_MEMORY)ft_garbage_collector.c \
		  $(DIR_MEMORY)calloc_gc.c $(DIR_MEMORY)free_gc.c \
		  $(DIR_MEMORY)malloc_gc.c
		  

F_NONE		= \033[37m
F_BOLD		= \033[1m
F_RED		= \033[31m
F_ORANGE	= \033[38m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m 

OBJS	= $(SRCS:.c=.o)


.c.o:
	$(CC) $(FLAGS) -c -I$(HEADER) $< -o $(<:.c=.o)
	@echo "$(F_BLUE)Object files libft in ready! $(F_NONE)"


all:	$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)
		@echo "$(F_YELLOW)libft.a COMPILE! $(F_NONE)"


clean:
		$(RM) $(OBJS) $(OBJBNS)
		@echo "$(F_GREEN)Cleaned! $(F_NONE)"

fclean:		clean
			$(RM) $(NAME)
			@echo "$(F_GREEN)FCleaned! $(F_NONE)"

re:	fclean all

norm:
	norminette *.c *.h

code:
	@echo " ~~~~~~~~~~~~~~~~"
	@echo "$(F_BOLD)  * Make code, *"
	@echo "$(F_BOLD)   * not war! *"
	@echo "$(F_RED)    ..10101.."
	@echo "$(F_ORANGE)  01   1   011"
	@echo "$(F_YELLOW) 10     0     00"
	@echo "$(F_GREEN) 11   .010.   11"
	@echo "$(F_CYAN) 00 .01 1 01. 10"
	@echo "$(F_BLUE) 010   1   110"
	@echo "$(F_BLUE)   11011010**$(F_NONE)"

.PHONY:     all clean fclean re bonus code
