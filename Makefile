# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergee <sergee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/03/01 20:04:28 by sergee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = rtv1.c handlers.c opencl.c parse.c check.c utility.c

HDR = rtv1.h

LIB = libft/libft.a

OBJ = $(SRC:.c=.o)

all:lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	gcc  -O3 -o $(NAME) $(OBJ) $(LIB) -F. -rpath . -framework OpenGl	\
	-framework AppKit -framework opencl -framework SDL2 -framework SDL2_ttf

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