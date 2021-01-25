# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarilli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/10 19:15:54 by bmarilli          #+#    #+#              #
#    Updated: 2020/12/26 18:18:24 by bmarilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MINIRT = miniRT

LIB_DIR =  ./libft/
LIB_NAME =	libft/libft.a
LIB_HEADER = libft/includes
MINILIBX = minilibx/libmlx.dylib
MINILIBXX = libmlx.dylib
LIBFT = libft.a

CC		= gcc

HEADER	= includes

FLAGS	= -Wall -Wextra -Werror 

OBJS	 = $(SRCS:.c=.o)
OBJS_GNL = $(GNL_SRCS:.c=.o)
OBJS_PARSER = $(PARSER_SRCS:.c=.o)
OBJS_ERROR = $(ERROR_SRCS:.c=.o)
OBJS_RayTracing = $(RayTracing_SRCS:.c=.o)
OBJS_RGB = $(RGB_SRCS:.c=.o)
OBJS_VEC = $(VEC_SRCS:.c=.o)

DIR		= ./srcs/
DIR_PARSER = ./srcs/parser/
DIR_GNL = ./srcs/gnl/
DIR_ERROR = ./srcs/error/
DIR_RayTracing = ./srcs/rt/
DIR_RGB = ./srcs/rgb/
DIR_VEC = ./srcs/vectors/

SRCS = $(DIR)main.c 
GNL_SRCS = $(DIR_GNL)get_next_line.c $(DIR_GNL)get_next_line_utils.c
PARSER_SRCS =	$(DIR_PARSER)ft_parse_rt.c	$(DIR_PARSER)ft_atoirgb.c 	$(DIR_PARSER)ft_atoi_xyz.c\
				$(DIR_PARSER)ft_parse_R.c	$(DIR_PARSER)ft_parse_A.c 	$(DIR_PARSER)ft_parse_c.c\
				$(DIR_PARSER)ft_parse_l.c	$(DIR_PARSER)ft_parse_sp.c	$(DIR_PARSER)ft_parse_cy.c\
				$(DIR_PARSER)ft_parse_pl.c	$(DIR_PARSER)ft_parse_sq.c	$(DIR_PARSER)ft_parse_tr.c

ERROR_SRCS = $(DIR_ERROR)ft_error.c
RayTracing_SRCS = 	$(DIR_RayTracing)start_rt.c $(DIR_RayTracing)cicle.c $(DIR_RayTracing)sphere.c \
					$(DIR_RayTracing)plane.c $(DIR_RayTracing)triangle.c $(DIR_RayTracing)square.c \
					$(DIR_RayTracing)cylinder.c
RGB_SRCS = $(DIR_RGB)rgb.c
VEC_SRCS = $(DIR_VEC)vectors.c

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
	@echo "$(F_BLUE)Created object files miniRT ! $(F_NONE)"
	$(CC) $(FLAGS) -c  -I$(HEADER) -I$(LIB_HEADER) $< -o $(<:.c=.o)
	@echo "$(F_BLUE)Object files miniRT in ready! $(F_NONE)"

all: $(LIBFT) $(MINILIBXX) $(NAME_MINIRT) 

bonus : $(LIBFT) $(MINILIBXX) $(NAME_MINIRT)	

$(MINILIBXX):
		@echo "$(F_CYAN)Copy libmlx.dylib ...$(F_NONE)"
		cp $(MINILIBX) $(MINILIBXX)
		@echo "$(F_CYAN)Copy libmlx.dylib END !...$(F_NONE)"

$(LIBFT):
		@echo "$(F_YELLOW)START RUN Makefile in libft $(F_NONE)"
		@$(MAKE) -C $(LIB_DIR)
		@echo "$(F_YELLOW)END RUN Makefile in libft $(F_NONE)"
$(NAME_MINIRT): $(OBJS) $(OBJS_GNL) $(OBJS_PARSER) $(OBJS_ERROR)  $(OBJS_RayTracing) $(OBJS_RGB) $(OBJS_VEC)
		@echo "$(F_CYAN)Compile miniRT ...$(F_NONE)"
		$(CC) $(FLAGS)  -I$(HEADER) $(OBJS) $(OBJS_GNL) $(OBJS_PARSER) $(OBJS_ERROR)  $(OBJS_RayTracing)  $(OBJS_RGB) $(OBJS_VEC) -L. $(LIB_NAME)  -lmlx -framework OpenGL -framework AppKit $(MINILIBX) -o $(NAME_MINIRT)
		@echo "$(F_GREEN)minRT is Ready! GOOD LUCK:) $(F_NONE)"		
clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS) $(OBJS_GNL) $(OBJS_PARSER) $(OBJS_ERROR) $(OBJS_RayTracing) $(OBJS_RGB) $(OBJS_VEC)
	@echo "$(F_GREEN)Cleaned! $(F_NONE)"
fclean: clean
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME_MINIRT)
	rm -rf $(MINILIBXX)
	@echo "$(F_GREEN)FCleaned! $(F_NONE)"

re: fclean all

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

.PHONY: all clean fclean re code bonus norm
