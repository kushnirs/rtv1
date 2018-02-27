# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergee <sergee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/02/26 19:33:58 by sergee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

# SRC = rtv1.c utility.c vector.c ray_obj.c light.c color.c handlers.c
SRC = rtv1_cl.c handlers.c opencl.c parse_param.c

# HDR = rtv1.h
HDR = rtv1_cl.h

LIB = libft/libft.a minilibx/libmlx.a

OBJ = $(SRC:.c=.o)

all:lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	gcc  -O3 -o $(NAME) $(OBJ) $(LIB) -F. -rpath . -framework OpenGl -framework AppKit -framework opencl -framework SDL2

.c.o:
	gcc  -O3 -c $< -F.

lib: 
	make -C libft;
clean:
	@make -C libft clean;
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean;
	@rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re
# -Wall -Wextra -Werror