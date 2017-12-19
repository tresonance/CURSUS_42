/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:04:33 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/07 22:22:36 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	chosen_fractal(t_env *e)
{
	if (e->fract == 1)
		fractale_man(e);
	else if (e->fract == 2)
		fractale_jul(e);
	else if (e->fract == 3)
		fractale_bship(e);
	else if (e->fract == 4)
		fractale_man2(e, 0, 0, 0);
	else if (e->fract == 5)
		fractale_man4(e, 0, 0, 0);
	else if (e->fract == 6)
		fractale_newton_love(e, 0, 0);
	else if (e->fract == 7)
		fractale_newton(e, 0, 0);
	else if (e->fract == 8)
		fractale_tricorn(e);
	else
		fractale_mandelbar4(e, 0, 0, 0);
}

void	draw_in_window(t_env *e)
{
	e->img = mlx_new_image(e->mlx, X, Y);
	e->data_img = mlx_get_data_addr(e->img, &(e->bpp),
			&(e->size_line), &(e->end));
	chosen_fractal(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	display_menu(e);
	mlx_destroy_image(e->mlx, e->data_img);
}

int		mouse_zoom(int key, int x, int y, t_env *e)
{
	double tmpx;
	double tmpy;

	tmpx = x / e->zoom + e->xmin;
	tmpy = y / e->zoom + e->ymin;
	if (key == IN)
		e->zoom /= 1.1;
	else if (key == OUT)
		e->zoom *= 1.1;
	e->xmin = tmpx - (x / e->zoom);
	e->ymin = tmpy - (y / e->zoom);
	draw_in_window(e);
	return (0);
}

int		mouse_change(int x, int y, t_env *e)
{
	if (x < X && x > 0 && y < Y && y > 0)
	{
		e->rc = (float)(x + 400 - X) / 500;
		e->ic = (float)(y + 400 - Y) / 500;
	}
	draw_in_window(e);
	return (0);
}

int		key(int key, t_env *e)
{
	e->ymin += (key == UP) ? 0.1 : 0;
	e->ymin -= (key == DOWN) ? 0.1 : 0;
	e->xmin += (key == LEFT) ? 0.1 : 0;
	e->xmin -= (key == RIGHT) ? 0.1 : 0;
	e->zoom *= (key == PLUS) ? 1.1 : 1;
	e->zoom /= (key == MOIN) ? 1.1 : 1;
	e->iter_max += (key == P_ITERATION) ? 5 : 0;
	e->iter_max -= (key == N_ITERATION) ? 5 : 0;
	(key == RESET) ? init_val(e) : 0;
	if (key == CHANGE)
	{
		if (e->fract < 9)
			e->fract++;
		else
			e->fract = 1;
		init_val(e);
	}
	draw_in_window(e);
	(key == ESC) ? exit(2) : 0;
	return (0);
}
