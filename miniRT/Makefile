# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/10 19:15:54 by bmarilli          #+#    #+#              #
#    Updated: 2020/12/10 19:22:34 by bmarilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MINIRT = miniRT

LIB_DIR =  ./libft/
LIB_NAME =	libft/libft.a
LIBFT = libft.a

CC		= gcc

HEADER	= ./includes

FLAGS	= -Wall -Wextra -Werror 

OBJS	= $(SRCS:.c=.o)

DIR		= ./srcs/

SRCS = $(DIR)main.c

AR		= ar rc

F_NONE		= \033[37m
F_BOLD		= \033[1m
F_RED		= \033[31m
F_ORANGE	= \033[38m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m

.c.o:
	$(CC) $(FLAGS) -c  -I$(HEADER) $< -o $(<:.c=.o)

all: $(LIBFT) $(NAME_MINIRT)

bonus : $(LIBFT) $(NAME_MINIRT)

$(LIBFT):
		@echo "Compile libft.a"
		@$(MAKE) -C $(LIB_DIR)
		@echo "Compile OK"
$(NAME_MINIRT): $(OBJS) 
		$(CC) $(FLAGS) -I$(HEADER) $(OBJS) -L. $(LIB_NAME) -o $(NAME_MINIRT)
		
clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)
fclean: clean
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME_MINIRT)

re: fclean all

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

.PHONY: all clean fclean re code bonus
