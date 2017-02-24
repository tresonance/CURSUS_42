/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 04:03:12 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:14:37 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void		place_piece(t_map *map, t_list *tmp, t_point point)
{
	int		i;
	int		j;
	t_piece *p;

	i = -1;
	p = (t_piece*)tmp->content;
	p->used = TRUE;
	while (++i < p->height)
	{
		j = -1;
		while (++j < p->width)
		{
			if (ft_isalpha(p->buff[i][j]) &&
					map->board[point.x + i][point.y + j] == '.')
				map->board[point.x + i][point.y + j] = p->c;
		}
	}
}

t_point		move(t_map *map, t_point point)
{
	point.y = point.y + 1;
	if (point.y == map->size)
	{
		point.x = point.x + 1;
		point.y = 0;
	}
	return (point);
}

t_point		origin(t_point point)
{
	point.x = 0;
	point.y = 0;
	return (point);
}

t_map		*solver(t_map *map, t_list **lst, t_point point)
{
	if (!*lst)
		return (map);
	if (point.x == map->size)
		return (NULL);
	if (is_fillable(map, *lst, point) == TRUE)
	{
		place_piece(map, *lst, point);
		if (solver(map, &(*lst)->next, origin(point)) == NULL)
		{
			remove_piece(map, *lst, point);
			return (solver(map, &(*lst), move(map, point)));
		}
		else
			return (map);
	}
	else
		return (solver(map, &(*lst), move(map, point)));
}
