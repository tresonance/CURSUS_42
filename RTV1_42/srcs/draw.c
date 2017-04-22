/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:44:58 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:13:33 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_color	get_color(int color)
{
	t_color	col;

	col.r = (color & 0xFF0000) >> 16;
	col.g = (color & 0xFF00) >> 8;
	col.b = (color & 0xFF);
	return (col);
}

t_color	ft_color(t_obj *hit_obj)
{
	t_color	col;

	col.r = (uint8_t)hit_obj->color.r;
	col.g = (uint8_t)hit_obj->color.g;
	col.g = (uint8_t)hit_obj->color.b;
	return (col);
}

void	pixel_put(int x, int y, t_color col, t_mlx mlx)
{
	int	index;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		index = y * mlx.size_line + (x * mlx.bpp / 8);
		mlx.data[index] = col.b;
		mlx.data[++index] = col.g;
		mlx.data[++index] = col.r;
	}
}
