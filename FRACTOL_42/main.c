/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:05:40 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/07 22:23:43 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(int x, int y, t_env *e)
{
	int	*ptr;
	int	index;

	if (y < Y && x < X && x > 0 && y > 0)
	{
		index = x * 4 + y * e->size_line;
		ptr = (int *)&e->data_img[index];
		if (e->iter_index == e->iter_max)
			*ptr = 0x000000;
		else
		{
			if (e->fract == 6)
				*ptr = 0x0000FF + (100000000 * e->iter_index) / 70;
			else
				*ptr = 0x8A0808 + (0x0000FF - e->iter_index);
		}
	}
}

void	put_pixel_color(int x, int y, t_env *e)
{
	int	*ptr;
	int	index;

	if (y < Y && x < X && x > 0 && y > 0)
	{
		index = x * 4 + y * e->size_line;
		ptr = (int *)&e->data_img[index];
		if (e->rz > 0)
			*ptr = 0xFF0000;
		else if ((e->rz < -0.3) && (e->iz > 0))
			*ptr = 0x00FF00;
		else
			*ptr = 0x0000FF;
	}
}

void	init_val(t_env *e)
{
	e->bloc = 0;
	e->xmin = -2.1;
	e->xmax = 0.6;
	e->ymin = -1.2;
	e->ymax = 1.2;
	e->iter_max = 25;
	e->zoom = 100;
	e->rc = 0.285;
	e->ic = 0.01;
}

void	ft_error(void)
{
	ft_putstr_fd("State a fractal number.\n", 2);
	ft_putstr_fd("1 : Mandelbrot.\n", 2);
	ft_putstr_fd("2 : Julia.\n", 2);
	ft_putstr_fd("3 : Burning Ship.\n", 2);
	ft_putstr_fd("4 : Mandelbrot p3.\n", 2);
	ft_putstr_fd("5 : Mandelbrot p4.\n", 2);
	ft_putstr_fd("6 : Newton Love.\n", 2);
	ft_putstr_fd("7 : Newton.\n", 2);
	ft_putstr_fd("8 : Mandelbar.\n", 2);
	ft_putstr_fd("9 : Mandelbar 4.\n", 2);
	exit(-1);
}

int		main(int ac, char **av)
{
	t_env e;

	if (ac != 2)
		ft_error();
	if (ft_strcmp(av[1], "1") == 0 || ft_strcmp(av[1], "2") == 0 ||
			ft_strcmp(av[1], "3") == 0 || ft_strcmp(av[1], "4") == 0 ||
			ft_strcmp(av[1], "5") == 0 || ft_strcmp(av[1], "6") == 0 ||
			ft_strcmp(av[1], "7") == 0 || ft_strcmp(av[1], "8") == 0 ||
			ft_strcmp(av[1], "9") == 0)
		e.fract = ft_atoi(av[1]);
	else
		ft_error();
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, X, Y, "FRACTOL");
	init_val(&e);
	draw_in_window(&e);
	mlx_hook(e.win, 2, 3, key, &e);
	mlx_hook(e.win, 6, 7, mouse_change, &e);
	mlx_mouse_hook(e.win, mouse_zoom, &e);
	mlx_loop(e.mlx);
}
