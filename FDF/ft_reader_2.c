/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 07:11:38 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 12:07:44 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_line(t_line **line, t_env *e)
{
	int i;

	if (!(*line = (t_line*)malloc(sizeof(t_line))))
		ft_err_exit("Unable to allocate");
	if (!((*line)->points = (t_point**)malloc(e->col * sizeof(t_point*))))
		ft_err_exit("Unable to allocate");
	i = -1;
	while (++i < e->col)
	{
		if (!((*line)->points[i] = (t_point*)malloc(sizeof(t_point))))
			ft_err_exit("Unable to allocate");
	}
}

void	get_map(t_map **map, t_env *e)
{
	int i;

	if (!(*map = (t_map*)malloc(e->col * sizeof(t_map))))
		ft_err_exit("Unable to allocate");
	if (!((*map)->lines = (t_line**)malloc(e->line * sizeof(t_line*))))
		ft_err_exit("Unable to allocate");
	i = -1;
	while (++i < e->line)
		get_line(&((*map)->lines[i]), e);
}

int		ft_color_palette(t_point p0, t_point p1)
{
	int color;
	int z;

	z = (p0.color > p1.color) ? p0.color : p1.color;
	if (z >= 0 && z < 10)
		color = 0x000097A7;
	else if (z >= 10 && z < 15)
		color = 0x003300FF;
	else if (z >= 15 && z < 30)
		color = 0x00E65100;
	else if (z >= 30 && z < 45)
		color = 0x00EAEBCA;
	else if (z >= 45 && z < 60)
		color = 0x0089E670;
	else if (z >= 60)
		color = 0x00FAD6CE;
	else
		color = 0x00FFFFFF;
	return (color);
}
