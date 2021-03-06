/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:08:39 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 08:53:52 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			untextured_map(int x, int y)
{
	static int map[22][22] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	return (map[x][y]);
}

void		init_env(t_env *e)
{
	e->endian = 0;
	e->bpp = 24;
	e->posx = 14;
	e->posy = 12;
	e->dirx = -1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.66;
	e->hit = 0;
	e->wallheight = 64;
	e->wallwidth = 64;
	e->perpwalldist = 0;
	e->rotspeed = M_PI / (double)48;
	e->translspeed = 0.1;
}

int			get_color(t_env *e)
{
	int color;

	color = 0x000000;
	if (e->side == 0 && e->raydirx < 0)
		color = 0x210518;
	else if (e->side == 0 && e->raydirx > 0)
		color = 0x4F0017;
	else if (e->side == 1 && e->raydiry < 0)
		color = 0x33040416;
	else if (e->side == 1 && e->raydiry > 0)
		color = 0x91311D;
	return (color);
}

void		put_pixel(int x, int y, int color, t_env *e)
{
	int		index;
	int		*ptr;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{
		index = y * e->size_line + (x * e->bpp / 8);
		ptr = (int *)&e->pixel[index];
		*ptr = color;
	}
}

void		draw_wall_ceiling_floor(int x, t_env *e)
{
	int i;
	int color;

	i = -1;
	color = get_color(e);
	while (++i < e->wallpixelstart)
		put_pixel(x, i, 0x3399ff, e);
	i = -1;
	while (++i < (e->wallpixelend - e->wallpixelstart))
		put_pixel(x, i + e->wallpixelstart, color, e);
	i = e->wallpixelend - 1;
	while (++i < HEIGHT)
	{
		if (i % 2 == 0)
			put_pixel(x, i, 0x0000cc, e);
		else
			put_pixel(x, i, 0xFFFFFF, e);
	}
}
