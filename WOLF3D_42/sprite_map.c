/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 07:58:11 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 09:21:30 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define X e->sprite[i].x_word
#define Y e->sprite[i].y_word
#define DIST e->sprite[i].dist_to_cam

int				sprite_map(int x, int y)
{
	static int sprit_maps[22][22] = {
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 6, 4, 4, 6, 4, 6, 4, 4, 4},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{8, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6},
	{8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 6, 0, 0, 0, 6},
	{7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 8, 0, 8, 0, 8, 0, 8, 4, 0, 4, 0, 6},
	{7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 0, 0, 0, 6},
	{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 0, 0, 4},
	{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 6, 0, 6},
	{7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 4, 6, 0, 6},
	{7, 7, 7, 7, 0, 7, 7, 7, 7, 8, 8, 4, 0, 6, 8, 4, 8, 3, 3, 3, 0, 3},
	{2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 6, 4, 0, 0, 6, 0, 6, 3, 0, 0, 0, 3},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 3},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 3},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 6, 0, 6, 3, 3, 0, 0, 3},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 2, 2, 2, 6, 6, 0, 0, 5, 0, 5},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 5},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 5},
	{2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5}};

	return (sprit_maps[x][y]);
}

void			set_sprites(t_sprite *sprite, double x, double y, int texture)
{
	sprite->x_word = x;
	sprite->y_word = y;
	sprite->texture = texture;
}

void			init_sprite1(t_env *e)
{
	int			i;

	set_sprites(&(e->sprite[0]), 20.5, 11.5, 10);
	set_sprites(&(e->sprite[1]), 18.5, 4.5, 10);
	set_sprites(&(e->sprite[2]), 10.0, 4.5, 10);
	set_sprites(&(e->sprite[3]), 10.0, 12.5, 10);
	set_sprites(&(e->sprite[4]), 3.5, 6.5, 10);
	set_sprites(&(e->sprite[5]), 3.5, 20.5, 10);
	set_sprites(&(e->sprite[6]), 3.5, 14.5, 10);
	set_sprites(&(e->sprite[7]), 14.5, 20.5, 10);
	set_sprites(&(e->sprite[8]), 18.5, 10.5, 9);
	set_sprites(&(e->sprite[9]), 18.5, 11.5, 9);
	set_sprites(&(e->sprite[10]), 18.5, 12.5, 9);
	set_sprites(&(e->sprite[11]), 21.5, 1.5, 8);
	set_sprites(&(e->sprite[12]), 15.5, 1.5, 8);
	set_sprites(&(e->sprite[13]), 16.0, 1.8, 8);
	set_sprites(&(e->sprite[14]), 16.2, 1.2, 8);
	set_sprites(&(e->sprite[15]), 3.5, 2.5, 8);
	set_sprites(&(e->sprite[16]), 9.5, 15.5, 8);
	set_sprites(&(e->sprite[17]), 10.0, 15.1, 8);
	set_sprites(&(e->sprite[18]), 10.5, 15.8, 8);
}

void			init_sprite(t_env *e)
{
	int			i;

	init_sprite1(e);
	i = -1;
	while (++i < SPRITE_NUM)
	{
		e->sprite[i].dist_to_cam = (e->posx - X) * (e->posx - X) +
		(e->posy - Y) * (e->posy - Y);
		e->spriteorder[i] = i;
	}
	sort_sprit_dist(e);
}

void			sort_sprit_dist(t_env *e)
{
	int			i;
	int			j;
	int			save;
	t_sprite	tmp;

	i = 0;
	j = 1;
	while (i < SPRITE_NUM - 1)
	{
		if (e->sprite[i].dist_to_cam < e->sprite[j].dist_to_cam)
		{
			tmp = e->sprite[i];
			e->sprite[i] = e->sprite[j];
			e->sprite[j] = tmp;
			save = e->spriteorder[i];
			e->spriteorder[i] = j;
			e->spriteorder[j] = save;
		}
		j += 1;
		if (j >= SPRITE_NUM)
		{
			i += 1;
			j = i + 1;
		}
	}
}
