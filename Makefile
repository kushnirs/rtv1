# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergee <sergee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/02/23 11:07:34 by sergee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = rtv1.c utility.c vector.c ray_obj.c light.c color.c handlers.c

HDR = rtv1.h

LIB = libft/libft.a minilibx/libmlx.a

OBJ = $(SRC:.c=.o)

all:lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	gcc  -O3 -o $(NAME) $(OBJ) $(LIB) -framework OpenGl -framework AppKit -framework opencl

.c.o:
	gcc  -O3 -c $< 

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