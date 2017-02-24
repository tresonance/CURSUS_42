/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:36:12 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:14:06 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_point					*get_point(int x, int y)
{
	t_point				*point;

	if (!(point = (t_point*)ft_memalloc(sizeof(t_point))))
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

void					min_max(char *buff, t_point *min, t_point *max)
{
	int					i;

	i = -1;
	while (++i < 20)
	{
		if (buff[i] == '#')
		{
			if (i / 5 < min->x)
				min->x = i / 5;
			if (i % 5 < min->y)
				min->y = i % 5;
			if (i / 5 > max->x)
				max->x = i / 5;
			if (i % 5 > max->y)
				max->y = i % 5;
		}
	}
}

t_piece					*get_piece(char *buff, char c)
{
	t_piece				*p;
	t_point				*mini;
	t_point				*maxi;
	int					i;

	if (!(p = ft_memalloc(sizeof(t_piece))))
		return (NULL);
	mini = get_point(20, 20);
	maxi = get_point(0, 0);
	min_max(buff, mini, maxi);
	p->height = maxi->x - mini->x + 1;
	p->width = maxi->y - mini->y + 1;
	p->c = c;
	p->buff = (char**)malloc(p->height * sizeof(char*));
	i = -1;
	while (++i < p->height)
	{
		p->buff[i] = (char*)malloc((p->width + 1) * sizeof(char));
		search_and_replace(buff, '#', p->c);
		ft_strncpy(p->buff[i], buff + (mini->x + i) * 5 + mini->y, p->width);
		p->buff[i][p->width] = '\0';
	}
	return (p);
}
