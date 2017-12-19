# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/26 00:15:03 by ibtraore          #+#    #+#              #
#    Updated: 2017/01/26 00:15:48 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
PATH_SRC = ./
PATH_OBJ = ./
PATH_INC = ./libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEAD = fdf.h

SRC =	main.c \
		ft_draw.c \
		ft_line.c \
		ft_matrix.c \
		ft_new_points.c \
		ft_reader.c \
		ft_reader_2.c\
		ft_destroyer.c\
		ft_hook.c\
		ft_hook_2.c

OBJ = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))


all: $(NAME)

$(NAME): $(OBJ) $(HEAD)
	make -C libft/
	$(CC) $(CFLAGS) -I $(PATH_INC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean
