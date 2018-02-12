# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergee <sergee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/02/08 11:24:17 by sergee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = rtv1.c utility.c vector.c

HDR = rtv1.h

LIB = libft/libft.a minilibx/libmlx.a

OBJ = $(SRC:.c=.o)

all:lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	gcc -Wall -Wextra -Werror -O3 -o $(NAME) $(OBJ) $(LIB) -framework OpenGl -framework AppKit -framework opencl

.c.o:
	gcc  -Wall -Wextra -Werror  -O3 -c $< 

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