# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 14:48:39 by thchin            #+#    #+#              #
#    Updated: 2017/12/15 15:43:20 by kmjaku           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

# GTK
LIB_GTK = `pkg-config --libs gtk+-3.0`
LIB_GTK_H = `pkg-config --cflags gtk+-3.0`

# Binary
NAME = rt

# Default RULES
DEFRULE = all

# Directories
SRCDIR = srcs
OBJDIR = objs

# LIBFT
LIBFT = ./libft
LIBS = make -C ./libft

ifeq ($(OS),Windows_NT)
	INCDIR = includes
	CFSDL =
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		ID_UN := $(shell id -un)
		INCDIR = includes\
				 /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.7/include/SDL2\
				 /Users/$(ID_UN)/.brew/Cellar/sdl2_image/2.0.2/include/SDL2\
				 -F framework Cocoa
		CFSDL =
	endif
	ifeq ($(UNAME_S),Linux)
		INCDIR = includes
		CFSDL = `sdl2-config --clflags`
	endif
endif

PREDIR = includes\

# Sources
SRC = main.c\
	  copy_scene.c\
	  event.c\
	  init_opencl.c\
	  init_scene.c\
	  init_skydome.c\
	  move_object.c\
	  perlin.c\
	  perm.c\
	  normal.c\
	  show.c\
	  time.c\
	  vector.c\
	  vector2.c\
	  count_obj.c\
	  convert_define.c\
	  parse_prim_co.c\
	  parse_text_co.c\
	  parse_co.c\
	  parse_bump_co.c\
	  parser.c\
	  gtk_widget_creator.c\
	  gtk_launch.c\
	  gtk_exit.c\
	  gtk_window_sdl.c\
	  gtk_kernel_info.c\
	  clean.c\
	  init_zero.c\
	  main_utils.c

OBJ = $(SRC:.c=.o)

# Prefixes
ifeq ($(OS),Windows_NT)
	OPNCL = -L/lib/ -lOpenCL
	LSDL2 = -lSDL2_image -lSDL2
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OPNCL = -framework OpenCL
		LSDL2 = -L/Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.7/lib -lSDL2\
				-L/Users/$(ID_UN)/.brew/Cellar/sdl2_image/2.0.2/lib -lSDL2_image
	endif
	ifeq ($(UNAME_S),Linux)
		OPNCL = -L/usr/lib/x86_64-linux-gnu -lOpenCL
		LSDL2 = `sdl2-config --libs` -lSDL2_image
	endif
endif

# Paths foreach
OBJP = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCP = $(foreach dir, $(INCDIR), -I$(dir))
PREP = $(addprefix $(PREDIR)/, $(PRECOMP))

# **************************************************************************** #
# SPECIAL CHARS

LOG_CLEAR		= \033[2K
LOG_UP			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BOLD		= \033[1m
LOG_UNDERLINE	= \033[4m
LOG_BLINKING	= \033[5m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# **************************************************************************** #
# RULES
.SILENT:

.PHONY: fclean clean

# Main rules
default:
	@echo -e "$(LOG_BOLD)Default execution: rule $(DEFRULE)$(LOG_NOCOLOR)"
	@make $(DEFRULE)
	@echo -e "$(LOG_BOLD)Execution finished     $(LOG_NOCOLOR)ヽ(ヅ)ノ"

all: $(OBJDIR) $(NAME)

re: fclean all

# Compilation rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -c -o $@ $^ $(INCP) $(CFSDL) $(LIB_GTK_H)

$(OBJDIR):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(NAME)$(LOG_NOCOLOR)"
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJP)
	$(LIBS)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -o $@ $^ $(OPNCL) $(LSDL2) -L $(LIBFT) -lft $(INCP) $(LIB_GTK) $(LIB_GTK_H)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(NAME)$(LOG_NOCOLOR) compiled.............. $(LOG_GREEN)✓$(LOG_NOCOLOR)"

clean:
	$(LIBS) clean
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)

fclean:
	$(LIBS) fclean
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJDIR)
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion.............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -f $(NAME)

# SDL2 brew
sdl2:
	brew install sdl2
	brew link sdl2
	brew install sdl2_image
	brew link sdl2_image
