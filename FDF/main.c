/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 07:28:33 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 10:14:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc != 2)
		ft_err_exit("Wrong parameter number");
	init_env(&e);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "fdf");
	ft_reader(&e, argv[1]);
	set_isometric_function(&e);
	set_image(&e);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
