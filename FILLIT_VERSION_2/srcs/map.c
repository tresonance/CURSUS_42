/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:50:08 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:14:14 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_map		*get_map(int size)
{
	t_map	*map;
	int		i;
	int		j;

	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->size = size;
	if (!(map->board = (char**)ft_memalloc(size * sizeof(char*))))
	{
		ft_memdel((void**)&map);
		return (NULL);
	}
	i = -1;
	while (++i < map->size)
	{
		map->board[i] = ft_strnew(map->size * sizeof(char));
		j = -1;
		while (++j < map->size)
			map->board[i][j] = '.';
	}
	return (map);
}

void		remove_piece(t_map *map, t_list *tmp, t_point point)
{
	t_piece *p;
	int		i;
	int		j;

	p = (t_piece*)tmp->content;
	p->used = FALSE;
	i = -1;
	while ((++i < p->height) && (point.x + i < map->size))
	{
		j = -1;
		while ((++j < p->width) && (point.y + j < map->size))
		{
			if (map->board[point.x + i][point.y + j] == p->c)
				map->board[point.x + i][point.y + j] = '.';
		}
	}
}

int			is_fillable(t_map *map, t_list *tmp, t_point point)
{
	int		i;
	int		j;
	int		bloc_counter;
	t_piece *p;

	i = -1;
	p = (t_piece*)tmp->content;
	bloc_counter = 0;
	if (!tmp)
		return (FALSE);
	while ((++i < p->height) && (point.x + i < map->size))
	{
		j = -1;
		while ((++j < p->width) && (point.y + j < map->size))
		{
			if (!(p->used) && ft_isalpha(p->buff[i][j])
					&& map->board[point.x + i][point.y + j] == '.')
			{
				if (++bloc_counter == 4)
					return (TRUE);
			}
		}
	}
	return (FALSE);
}

void		print_map(t_map *map)
{
	int		i;
	int		j;

	i = -1;
	if (!map)
		return ;
	while (++i < map->size)
	{
		j = -1;
		while (++j < map->size)
			ft_putchar(map->board[i][j]);
		ft_putchar('\n');
	}
}
