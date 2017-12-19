# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thou <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/04 17:35:06 by thou              #+#    #+#              #
#    Updated: 2017/09/20 15:49:10 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	\033[30;1m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
YELLOW		=	\033[33;1m
BLUE		=	\033[34;1m
PURPLE		=	\033[35;1m
CYAN		=	\033[36;1m
WHITE		=	\033[37;1m
RESET		=	\033[0m
CLEAR		=	\033[H\e[J

NAME		=	rt
FLAG		=	-Wall -Werror -Wextra -g
FLAGMLX		=	-lmlx -framework OpenGL -framework Appkit
SRC_DIR		=	src/
SRC_BASE	=	algebre.c base_change.c obj_first_position.c\
		 		block.c brick.c camera_hook.c translate_camera.c  rotate_camera.c translate_light.c\
			chessboard.c color.c cone.c cubic_solver.c\
			cuboid.c cylinder.c destroyer.c display_cam_info.c display_obj_info.c draw.c general_obj_data.c general_obj_data2.c general_obj_data3.c general_obj_data4.c\
			initializer.c  list.c main.c procedural_color.c\
			particulary_data.c plane.c selection.c textured_cone.c\
			quadratic_solver.c quartic_solver.c ray.c read_file.c\
			reflection.c light_color.c refraction.c\
			scene.c  sphere.c store_camera_data.c store_obj_data.c\
			texture.c textured_sphere.c textured_cuboid.c trace.c\
			utils.c vector.c mouse_hook.c triangle.c textured_cylinder.c\
			textured_plane.c textured_triangle.c list_remove_if.c thinring.c torus.c mobius.c pthread.c\
		cuboid_utils1.c  cuboid_utils2.c perlin.c interpolate.c csg.c box.c line.c aabb.c

SRC		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ_DIR		=	obj/
LIBFT		=	./libft
LFT			=	./libft/libft.a
LIBMLX		=	./minilibx_macos
LMLX		=	./minilibx_macos/libmlx.a
INCLUDES	=	-I./includes -I./libft/includes -I./minilibx/
FT_LNK		= 	-l pthread
OBJ			=	$(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

all: $(LFT) $(LMLX) $(NAME)

$(LFT):
	@make -C $(LIBFT)

$(LMLX):
	@echo "make libmlx ..."
	@make -C $(LIBMLX) 1>/dev/null 2>&1
	@echo "\033[1A\033[48;5;15;38;5;25;1mMAKE LIBMLX DONE$(RESET)"

$(NAME): $(OBJ)
	@gcc $(FLAG) $(OBJ) -o $(NAME) -L$(LIBFT) -lft -L$(LIBMLX) $(FLAGMLX) $(INCLUDES) $(FT_LNK)
	@echo "\033[48;5;15;38;5;25;1mMAKE $(NAME) DONE$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAG) -o $@ -c $< $(INCLUDES)


clean:
	@make clean -C $(LIBMLX)
	@make clean -C $(LIBFT)
	@rm -rf obj

fclean: 
	@make fclean -C $(LIBFT)
	@make clean -C $(LIBMLX) 1>/dev/null
	@echo "$(YELLOW)Clean   LIBMLX$(GREEN)			[ OK ]$(RESET)"
	@rm -rf obj
	@rm -rf $(NAME)
	@echo "$(YELLOW)Clean	$(NAME)$(GREEN)			[ OK ]$(RESET)"

re: fclean all
