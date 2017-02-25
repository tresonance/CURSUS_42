/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 02:09:29 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 08:42:25 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		hit3(t_env *e)
{
	while (!e->hit)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if (sprite_map(e->mapx, e->mapy) > 0)
			e->hit = 1;
	}
}

void		perpdist_lineheight_calcul3(int x, t_env *e)
{
	e->perpwalldist = (e->side == 0) ? (-1 * e->rayposx + e->mapx +
	(1 - e->stepx) / 2) / e->raydirx : (-1 * e->rayposy + e->mapy +
	(1 - e->stepy) / 2) / e->raydiry;
	e->lineheight = (int)(HEIGHT / e->perpwalldist);
	e->wallpixelstart = HEIGHT / 2 - e->lineheight / 2;
	if (e->wallpixelstart < 0)
		e->wallpixelstart = 0;
	e->wallpixelend = HEIGHT / 2 + e->lineheight / 2;
	if (e->wallpixelstart >= HEIGHT)
		e->wallpixelend = HEIGHT - 1;
	e->zbuffer[x] = e->perpwalldist;
}

void		sprite_raycasting(t_env *e)
{
	int x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_direction(x, e);
		sidedist_calcul(e);
		hit3(e);
		perpdist_lineheight_calcul3(x, e);
		draw_game3(e, x);
	}
	draw_sprite(e);
}
