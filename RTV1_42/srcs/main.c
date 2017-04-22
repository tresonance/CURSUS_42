/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 10:14:37 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/22 02:34:48 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2)
	{
		e.obj = NULL;
		if (0 == get_scene(&e.obj, &e.cam, argv[1]))
		{
			printf("Error\n");
			return (1);
		}
		e.mlx.mlx = mlx_init();
		e.mlx.win = mlx_new_window(e.mlx.mlx, WIDTH, HEIGHT, "rtv1");
		e.mlx.img = mlx_new_image(e.mlx.mlx, WIDTH, HEIGHT);
		e.mlx.data = mlx_get_data_addr(e.mlx.img, &e.mlx.bpp, &e.mlx.size_line,
										&e.mlx.endian);
		e.aa = 1.0;
		e.up = (t_vector){0.0, 1.0, 0.0};
		draw_obj(&e);
		mlx_key_hook(e.mlx.win, key_hook, &e);
		mlx_loop(e.mlx.mlx);
	}
	return (0);
}
