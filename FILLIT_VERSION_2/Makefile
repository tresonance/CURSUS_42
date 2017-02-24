FILLIT = fillit
NAME = $(FILLIT)
LIBFT = libft.a
GCC_FLAGS = -Wall -Werror -Wextra
CC = gcc $(GCC_FLAGS)
RM = rm -rf

SRCS =  file_checker.c\
	   reader.c\
	   init_data.c\
	   map.c\
	   solver.c\
	   destroyer.c

SRCDIR = ./srcs/
OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -L ./libft/ $(OBJS) -lft -o $(NAME)

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $^

$(LIBFT):
	@make -C ./libft/

clean:
	@$(RM) $(OBJS)
	@make clean -C ./libft/

fclean: clean
	@$(RM) $(LIBFT)
	@$(RM) $(NAME)
	@make fclean -C ./libft/

re: fclean all
