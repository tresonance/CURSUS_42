/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:56:50 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 03:45:02 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		wait_rot_event(int key, t_env *e)
{
	if (key == RIGHT)
	{
		e->tmp1 = e->dirx;
		e->dirx = e->dirx * cos(-e->rotspeed) - e->diry * sin(-e->rotspeed);
		e->diry = e->tmp1 * sin(-e->rotspeed) + e->diry * cos(-e->rotspeed);
		e->tmp2 = e->planex;
		e->planex = e->planex * cos(-e->rotspeed) - e->planey *
		sin(-e->rotspeed);
		e->planey = e->tmp2 * sin(-e->rotspeed) + e->planey *
		cos(-e->rotspeed);
	}
	if (key == LEFT)
	{
		e->tmp1 = e->dirx;
		e->dirx = e->dirx * cos(e->rotspeed) - e->diry * sin(e->rotspeed);
		e->diry = e->tmp1 * sin(e->rotspeed) + e->diry * cos(e->rotspeed);
		e->tmp2 = e->planex;
		e->planex = e->planex * cos(e->rotspeed) - e->planey *
		sin(e->rotspeed);
		e->planey = e->tmp2 * sin(e->rotspeed) + e->planey * cos(e->rotspeed);
	}
}

void		wait_translate_event(int key, t_env *e)
{
	if (key == UP)
	{
		if (untextured_map(((int)(e->posx + e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx += e->dirx * e->translspeed;
		if (untextured_map(((int)e->posx), ((int)(e->posy + e->diry *
			e->translspeed)) == 0))
			e->posy += e->diry * e->translspeed;
	}
	if (key == DOWN)
	{
		if (untextured_map(((int)(e->posx - e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx -= e->dirx * e->translspeed;
		if (untextured_map(((int)e->posx), ((int)(e->posy - e->diry *
			e->translspeed)) == 0))
			e->posy -= e->diry * e->translspeed;
	}
}

void		wait_translate_event2(int key, t_env *e)
{
	if (key == UP)
	{
		if (textured_map(((int)(e->posx + e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx += e->dirx * e->translspeed;
		if (textured_map(((int)e->posx), ((int)(e->posy + e->diry *
			e->translspeed)) == 0))
			e->posy += e->diry * e->translspeed;
	}
	if (key == DOWN)
	{
		if (textured_map(((int)(e->posx - e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx -= e->dirx * e->translspeed;
		if (textured_map(((int)e->posx), ((int)(e->posy - e->diry *
			e->translspeed)) == 0))
			e->posy -= e->diry * e->translspeed;
	}
}

void		wait_translate_event3(int key, t_env *e)
{
	if (key == UP)
	{
		if (sprite_map(((int)(e->posx + e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx += e->dirx * e->translspeed;
		if (sprite_map(((int)e->posx), ((int)(e->posy + e->diry *
			e->translspeed)) == 0))
			e->posy += e->diry * e->translspeed;
	}
	if (key == DOWN)
	{
		if (sprite_map(((int)(e->posx - e->dirx * e->translspeed)),
			((int)e->posy)) == 0)
			e->posx -= e->dirx * e->translspeed;
		if (sprite_map(((int)e->posx), ((int)(e->posy - e->diry *
			e->translspeed)) == 0))
			e->posy -= e->diry * e->translspeed;
	}
}

void		increase_decrease_movement_speed(int key, t_env *e)
{
	e->rotspeed += (key == INCREASE_ROT_SPEED && e->rotspeed <= M_PI /
	(double)3)
		? 0.1 : 0;
	e->rotspeed -= (key == DECREASE_ROT_SPEED && e->rotspeed >= M_PI /
	(double)48) ? 0.1 : 0;
	e->translspeed += (key == INCREASE_TRANSL_SPEED && e->translspeed < 0.7) ?
	0.1 : 0;
	e->translspeed -= (key == DECREASE_TRANSL_SPEED && e->translspeed > 0.2) ?
	0.1 : 0;
}
