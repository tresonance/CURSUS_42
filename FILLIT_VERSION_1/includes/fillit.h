/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 03:27:56 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 03:28:00 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define BUF_SIZE 1000

typedef	struct	s_fillit
{
	char	**tetris;
	char	**map;
	int		tetris_nbr;
	int		size_map_min;
}				t_fillit;

int				map_check(char *av, t_fillit *fillit);
int				nb_tetris(char *map);
int				ft_sqrt(int nb);
void			ft_destroy_map(char **map);
char			*ft_push_left(char *tetris);
char			*ft_push_top(char *tetris, char letter, int i, int y);
char			**ft_creat_map(t_fillit *fillit);
char			*ft_reduce_tetris(char *str, int i, int j, int sharp);
void			ft_resolve(t_fillit *fillit);
int				is_fillable(t_fillit *fllit, char *tetris, int x, int y);
char			*map_recup(char *av);

#endif
