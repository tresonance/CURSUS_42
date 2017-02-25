/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 04:02:07 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 04:05:08 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		load_textured_sprite_img(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH + 100, HEIGHT + 100);
	e->pixel = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line),
	&(e->endian));
	sprite_raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_string_put(e->mlx, e->win, 800, 5, 0xFFFFFF, "Rot Speed: A+/S-");
	mlx_string_put(e->mlx, e->win, 800, 35, 0xFFFFFF, "Transl Speed: Q+/W-");
	mlx_string_put(e->mlx, e->win, 800, 70, 0xFFFFFF, "Reset: R");
	mlx_destroy_image(e->mlx, e->img);
}

void		load_untextured_img(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH + 100, HEIGHT + 100);
	e->pixel = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line),
	&(e->endian));
	untextured_raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_string_put(e->mlx, e->win, 800, 5, 0xFFFFFF, "Rot Speed: A+/S-");
	mlx_string_put(e->mlx, e->win, 800, 35, 0xFFFFFF, "Transl Speed: Q+/W-");
	mlx_string_put(e->mlx, e->win, 800, 70, 0xFFFFFF, "Reset: R");
	mlx_destroy_image(e->mlx, e->img);
}
