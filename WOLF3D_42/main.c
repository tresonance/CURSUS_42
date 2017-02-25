/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 09:26:32 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 06:26:53 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		load_textured_img(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH + 100, HEIGHT + 100);
	e->pixel = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line),
	&(e->endian));
	textured_raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_string_put(e->mlx, e->win, 800, 5, 0xFFFFFF, "Rot Speed: A+/S-");
	mlx_string_put(e->mlx, e->win, 800, 35, 0xFFFFFF, "Transl Speed: Q+/W-");
	mlx_string_put(e->mlx, e->win, 800, 70, 0xFFFFFF, "Reset: R");
	mlx_destroy_image(e->mlx, e->img);
}

void		untextured(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "UNTEXTURED WOLF3D");
	init_env(e);
	load_untextured_img(e);
	mlx_hook(e->win, 2, 3, wait_key_event, e);
	mlx_hook(e->win, 17, 18, close_window, e->mlx);
	mlx_loop(e->mlx);
	mlx_destroy_window(e->mlx, e->win);
}

void		textured(t_env *e)
{
	t_game	*g;

	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "TEXTURED WOLF3D");
	init_env2(e);
	load_textured_img(e);
	mlx_hook(e->win, 2, 3, wait_key_event2, e);
	mlx_hook(e->win, 17, 18, close_window, e->mlx);
	mlx_loop(e->mlx);
	mlx_destroy_window(e->mlx, e->win);
}

void		textured_sprite(t_env *e)
{
	t_game	*g;

	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "TEXTURED SPRITES WOLF3D");
	init_env3(e);
	load_textured_sprite_img(e);
	mlx_hook(e->win, 2, 3, wait_key_event3, e);
	mlx_hook(e->win, 17, 18, close_window, e->mlx);
	mlx_loop(e->mlx);
	mlx_destroy_window(e->mlx, e->win);
}

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2)
	{
		e.frame_num = ft_atoi(argv[1]);
		if (e.frame_num > 0 && e.frame_num < 4)
		{
			e.mlx = mlx_init();
			if (e.frame_num == 1)
				untextured(&e);
			else if (e.frame_num == 2)
				textured(&e);
			else
				textured_sprite(&e);
		}
		else
			ft_putstr_fd("---Wrong file number---\nState 1, 2, 3\n", 2);
	}
	else
		err_exit("Warning :Wrong argument number.\nUsage:/wolf [file num]", 2);
	return (0);
}
