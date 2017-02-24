/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:21:20 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:15:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# define BUFF_SIZE 21
# define TRUE 1
# define FALSE 0

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_piece
{
	char		**buff;
	char		c;
	int			used;
	int			width;
	int			height;
}				t_piece;

typedef struct	s_map
{
	int			size;
	char		**board;
}				t_map;

void			err_exit(void);
int				valid_char(char *buff, int ret);
int				connection(char *buff);
t_piece			*get_piece (char *buff, char c);
void			free_piece(t_piece **p);
void			free_list(t_list **lst);
void			free_map(t_map **map);
t_map			*get_map(int size);
void			print_map(t_map *map);
void			search_and_replace(char *buff, char a, char b);
int				is_fillable (t_map *map, t_list *tmp, t_point point);
void			remove_piece(t_map *map, t_list *tmp, t_point point);
t_map			*solver(t_map *map, t_list **lst, t_point point);
#endif
