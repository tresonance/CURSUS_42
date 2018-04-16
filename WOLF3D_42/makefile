# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 03:13:29 by ibtraore          #+#    #+#              #
#    Updated: 2017/02/24 09:15:45 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC = main.c\
	  textured_map.c\
	  textured_wolf.c\
	  untextured_map.c\
	  untextured_wolf.c\
	  ft_hook.c\
	  ft_hook2.c\
	  draw_textured_map.c\
	  musique.c\
	  sprite_map.c\
	  sprite_map_init.c\
	  sprite_map2.c\
	  sprite_wolf.c\
	  main_rest.c\
	  with_sprite.c

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAG = -Wall -Wextra -Werror -L./libft -lft -lmlx -L./minilibx_macos -framework OpenGL -framework AppKit


all: $(NAME)

$(NAME): $(OBJ)
	 	@mkdir OBJ
	 	@make -C libft/
		@gcc $(OBJ) -o $(NAME) $(CFLAG) -g3
		@mv $(OBJ) obj
		@echo "WOLF3D COMPILATION DONE"

.PHONY: $(NAME) all clean fclean re


clean:
		@rm -rf obj
		@make  -C libft/ clean
		@rm -rf $(NAME)
		@rm -rf *.o

fclean: clean
		@make fclean -C libft/ 
		@rm -rf $(NAME)
		@rm -rf *.o
		@echo "WOLF3D FCLEAN DONE"

re: fclean $(NAME)


