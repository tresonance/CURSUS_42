# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/19 06:00:44 by ibtraore          #+#    #+#              #
#    Updated: 2016/11/20 03:02:26 by ibtraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_memset.c \
		ft_bzero.c \
		ft_countwords.c\
		ft_memcpy.c \
		ft_strtrim.c \
		ft_strsub.c \
		ft_strsplit.c \
		ft_strnew.c \
		ft_strnequ.c \
		ft_strmapi.c \
		ft_strmap.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_striteri.c \
		ft_striter.c \
		ft_strequ.c \
		ft_strdup.c \
		ft_strndup.c\
		ft_strdel.c \
		ft_strcpy.c \
		ft_strclr.c \
		ft_memdel.c \
		ft_memalloc.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_atoi.c \
		ft_abs.c\
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c\
		ft_iswhitespace.c\
		ft_itoa.c\
		ft_memmove.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memcpy.c \
		ft_strmerge.c\
		ft_strstr.c \
		ft_strcat.c \
		ft_strncpy.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_putnbr_fd.c \
		ft_max.c\
		ft_memcmp.c \
		ft_memchr.c \
		ft_memccpy.c \
		ft_putendl_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ = $(SRC:.c=.o)

RM = @rm -f

$(NAME): $(OBJ)
	gcc $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
