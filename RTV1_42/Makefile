# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/26 00:15:03 by ibtraore          #+#    #+#              #
#    Updated: 2017/05/10 23:18:35 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = gcc
LIB_NAME = ft
LIBDIR = libft
FLAGS = -Wall -Wextra -Werror #-fsanitize=address

HEADERS = includes

HEAD = rtv.h

SOURCES = srcs/inter_utils.c\
		  srcs/vector.c\
		  srcs/vector2.c\
		  srcs/file_to_cam.c\
		  srcs/file_to_obj.c\
		  srcs/ray.c\
		  srcs/objet_hit.c\
		  srcs/inter.c\
		  srcs/list.c\
		  srcs/color.c\
		  srcs/draw.c\
		  srcs/closest_t.c\
		  srcs/translate_light.c\
		  srcs/light_composantes.c\
		  srcs/get_light2.c\
		  srcs/clear.c\
		  srcs/mouse_hook.c\
		  srcs/display_cam_info.c\
		  srcs/display_obj_info.c\
		  srcs/main.c\
		  srcs/get.c\
		  srcs/hook.c\
		  srcs/translate_event.c\
		  srcs/rotate_event.c\
		  srcs/get_scene.c\
		  srcs/copy.c\

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(LIBDIR)/lib$(LIB_NAME).a $(OBJECTS)
	 @$(CC) $(FLAGS) -L $(LIBDIR) -l $(LIB_NAME) -o $@ $^ -lmlx  -L./minilibx_macos -framework OpenGL -framework AppKit -lpthread
	  @echo "compiling [ $(NAME) ] SUCCESS"

$(LIBDIR)/lib$(LIB_NAME).a :
	 @$(MAKE) -C $(LIBDIR)

all: $(NAME)

%.o: %.c $(HEADERS)/rtv1.h
	 @$(CC) $(FLAGS) -I $(HEADERS) -c $< -o $@

clean:
	 @rm -f $(OBJECTS)
	  @make clean -C $(LIBDIR)

fclean: clean
	 @rm -f $(NAME)
	  @make fclean -C $(LIBDIR)

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
