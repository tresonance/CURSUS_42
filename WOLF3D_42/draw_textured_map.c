/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 09:22:06 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 06:56:00 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		texture_xy_pixel(t_env *e, t_game *g)
{
	g->textured_map_value = textured_map(e->mapx, e->mapy) - 1 >= 0 ?
		textured_map(e->mapx, e->mapy) - 1 : 0;
	if (e->side == 0)
		e->wallxy = e->rayposx + e->perpwalldist * e->raydirx;
	else
		e->wallxy = e->rayposy + e->perpwalldist * e->raydiry;
	e->wallxy -= floor((e->wallxy));
	g->texture[g->textured_map_value]->x = (int)(e->wallxy * TEXTURE_WIDTH);
	if (e->side == 0 && e->raydirx > 0)
		g->texture[g->textured_map_value]->x = TEXTURE_WIDTH -
		g->texture[g->textured_map_value]->x - 1;
	if (e->side == 1 && e->raydiry < 0)
		g->texture[g->textured_map_value]->x = TEXTURE_WIDTH -
		g->texture[g->textured_map_value]->x - 1;
}

void		draw_wall(t_env *e, t_game *g, int x)
{
	int		y;
	int		color;

	y = e->wallpixelstart - 1;
	while (++y < e->wallpixelend)
	{
		g->texture[g->textured_map_value]->y = (y * 2 - HEIGHT +
				e->lineheight) * (TEXTURE_HEIGHT / 2) / e->lineheight;
		color = *((int *)&g->texture[g->textured_map_value]->imgptr[g->texture
				[g->textured_map_value]->y * g->texture[g->textured_map_value]
				->size_line + g->texture[g->textured_map_value]->x * g->texture
				[g->textured_map_value]->bpp / 8]);
		if (e->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(x, y, color, e);
	}
}

void		draw_game(t_env *e, int x)
{
	int		y;
	int		color;
	t_game	*g;

	g = e->g;
	texture_xy_pixel(e, g);
	y = -1;
	while (++y < e->wallpixelstart)
	{
		color = *((int *)&g->texture[8]->imgptr[y % g->texture[8]->height *
		g->texture[8]->size_line + x % g->texture[8]->width *
		g->texture[8]->bpp / 8]);
		put_pixel(x, y, color, e);
	}
	draw_wall(e, g, x);
	y = e->wallpixelend - 1;
	while (++y < HEIGHT)
	{
		color = *((int *)&g->texture[3]->imgptr[y % g->texture[3]->height *
		g->texture[3]->size_line + x % g->texture[3]->width *
		g->texture[3]->bpp / 8]);
		put_pixel(x, y, color, e);
		put_pixel(x, y, 0x687483, e);
	}
}
