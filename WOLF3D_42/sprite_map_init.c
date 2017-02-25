/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 07:58:11 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 09:18:08 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define X e->sprite[i].x_word
#define Y e->sprite[i].y_word
#define DIST e->sprite[i].dist_to_cam

void			get_sprite_xy_in_camera_space(int i, t_env *e)
{
	double		spritex;
	double		spritey;
	double		invmatrix;

	invmatrix = 1.0 / (e->planex * e->diry - e->planey * e->dirx);
	spritex = e->sprite[e->spriteorder[i]].x_word - e->posx;
	spritey = e->sprite[e->spriteorder[i]].y_word - e->posy;
	e->sprite[i].sprite_x_camspace = invmatrix * (e->diry * spritex -
	e->dirx * spritey);
	e->sprite[i].sprite_y_camspace = invmatrix * (-1.0 * e->planey * spritex
	+ e->planex * spritey);
	e->sprite[i].leftright = (int)((WIDTH / 2) * (1 +
	e->sprite[i].sprite_x_camspace / e->sprite[i].sprite_y_camspace));
}

void			get_sprite_height_info(int i, t_env *e)
{
	e->sprite[i].height_reduced = abs((int)(HEIGHT /
	e->sprite[i].sprite_y_camspace));
	e->sprite[i].height_pixel_start = HEIGHT / 2 -
	e->sprite[i].height_reduced / 2;
	if (e->sprite[i].height_pixel_start < 0)
		e->sprite[i].height_pixel_start = 0;
	e->sprite[i].height_pixel_end = HEIGHT / 2 +
	e->sprite[i].height_reduced / 2;
	if (e->sprite[i].height_pixel_end >= HEIGHT)
		e->sprite[i].height_pixel_end = HEIGHT - 1;
	e->sprite[i].width_reduced = abs((int)(HEIGHT /
	e->sprite[i].sprite_y_camspace));
	e->sprite[i].width_pixel_start = -e->sprite[i].width_reduced / 2 +
	e->sprite[i].leftright;
	if (e->sprite[i].width_pixel_start < 0)
		e->sprite[i].width_pixel_start = 0;
	e->sprite[i].width_pixel_end = e->sprite[i].leftright +
	e->sprite[i].width_reduced / 2;
	if (e->sprite[i].width_pixel_end >= WIDTH)
		e->sprite[i].height_pixel_end = WIDTH - 1;
}
