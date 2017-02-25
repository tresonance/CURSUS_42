/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_wolf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 07:14:35 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 08:02:54 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		hit2(t_env *e)
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
		if (textured_map(e->mapx, e->mapy) > 0)
			e->hit = 1;
	}
}

void		textured_raycasting(t_env *e)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_direction(x, e);
		sidedist_calcul(e);
		hit2(e);
		perpdist_lineheight_calcul(e);
		draw_game(e, x);
	}
}
