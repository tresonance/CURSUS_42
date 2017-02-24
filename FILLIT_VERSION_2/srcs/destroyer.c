/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:47:24 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:13:41 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void			free_piece(t_piece **p)
{
	int			i;

	i = -1;
	if (*p)
	{
		while (++i < (*p)->height)
			ft_strdel(&((*p)->buff[i]));
		ft_memdel((void**)&(*p));
	}
}

void			free_list(t_list **lst)
{
	t_list		*tmp;
	t_piece		*p;

	if (*lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = tmp->next;
			p = (t_piece*)tmp->content;
			ft_memdel((void**)&p);
			ft_memdel((void**)&tmp);
		}
	}
}

void			free_map(t_map **map)
{
	int			i;

	i = -1;
	if (*map)
	{
		while (++i < (*map)->size)
			ft_strdel(&(*map)->board[i]);
		ft_memdel((void**)&(*map));
	}
}
