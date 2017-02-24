# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 23:06:40 by ibtraore          #+#    #+#              #
#    Updated: 2016/12/21 03:28:39 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
SRC_DIR = ./srcs/
RM = rm -f
CC = gcc -Wall -Werror -Wextra -I ./include
SRC = main.c \
	   ft_resolve.c \
	   ft_creat_map.c \
	   ft_reader.c \
	   ft_move.c \
	   map_check.c
VPATH = $(SRC_DIR)
OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))
O_DIR = ./objs

$(NAME): $(OBJ)
	@echo "Making library."
	make -C libft/
	@echo "Library made."
	@echo "Making exe."
	@gcc -o $(NAME) -Werror -Wextra -Wall -I includes/ $(OBJ) -L libft/ -lft

$(O_DIR)/%.o: %.c
	@mkdir -p $(O_DIR)
	@gcc -Wall -Werror -Wextra -ferror-limit=2 -I includes -o $@ -c $<	

all: $(NAME)

clean:
	@echo "Removing objets."
	@rm -rf ./objs
	@make clean -C libft/ 
	@echo "Clean done."


fclean: clean
	@echo "Removing exe."
	$(RM) $(NAME)
	@make fclean -C libft/ 
	@echo "Fclean done."

re: fclean all
