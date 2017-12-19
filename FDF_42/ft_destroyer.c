/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:30 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 09:20:56 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(".\n", 2);
	exit(-1);
}

void		ft_destroy_tab(char **tab)
{
	int		i;

	i = -1;
	if (*tab)
	{
		while (tab[++i])
			ft_strdel(&tab[i]);
		ft_memdel((void **)tab);
	}
}

void		ft_destroy_line(t_line **line, t_env *e)
{
	int		i;

	i = -1;
	if (*line)
	{
		while (++i < e->col)
			ft_memdel((void **)&((*line)->points[i]));
		ft_memdel((void **)line);
	}
}

void		ft_destroy_map(t_env *e)
{
	int i;

	i = -1;
	if (e->map)
	{
		while (++i < e->line)
			ft_destroy_line(&((e->map)->lines[i]), e);
		ft_memdel((void **)e->map);
	}
}
