/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured_wolf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 07:13:32 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 08:27:24 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ray_direction(int x, t_env *e)
{
	e->camerax = (2 * x) / (double)WIDTH - 1;
	e->rayposx = e->posx;
	e->rayposy = e->posy;
	e->hit = 0;
	e->raydirx = e->dirx + e->camerax * e->planex;
	e->raydiry = e->diry + e->camerax * e->planey;
	e->mapx = (int)e->rayposx;
	e->mapy = (int)e->rayposy;
	e->deltadistx = sqrt(1 + (e->raydiry * e->raydiry) /
			(e->raydirx * e->raydirx));
	e->deltadisty = sqrt(1 + (e->raydirx * e->raydirx) /
			(e->raydiry * e->raydiry));
}

void		sidedist_calcul(t_env *e)
{
	if (e->raydirx < 0)
	{
		e->sidedistx = (e->rayposx - e->mapx) * e->deltadistx;
		e->stepx = -1;
	}
	else
	{
		e->sidedistx = (e->mapx + 1.0 - e->rayposx) * e->deltadistx;
		e->stepx = 1;
	}
	if (e->raydiry < 0)
	{
		e->sidedisty = (e->rayposy - e->mapy) * e->deltadisty;
		e->stepy = -1;
	}
	else
	{
		e->sidedisty = (e->mapy + 1.0 - e->rayposy) * e->deltadisty;
		e->stepy = 1;
	}
}

void		hit(t_env *e)
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
		if (untextured_map(e->mapx, e->mapy) > 0)
			e->hit = 1;
	}
}

void		perpdist_lineheight_calcul(t_env *e)
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
}

void		untextured_raycasting(t_env *e)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_direction(x, e);
		sidedist_calcul(e);
		hit(e);
		perpdist_lineheight_calcul(e);
		draw_wall_ceiling_floor(x, e);
	}
}
