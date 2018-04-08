/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:06:46 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/07 22:24:10 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	display_menu(t_env *e)
{
		mlx_string_put(e->mlx, e->win, 5, 5 /*340*/, 0XFFFFFF, "IBTRAORE SCHOOL 42");
	if (e->fract == 1)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "1- Mandelbrot");
	else if (e->fract == 2)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "2- Julia");
	else if (e->fract == 3)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "3- Burning Ship");
	else if (e->fract == 4)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "4- Mandelbrot P3");
	else if (e->fract == 5)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "5- Mandelbrot P4");
	else if (e->fract == 6)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "6- Newton V1");
	else if (e->fract == 7)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "7- Newton V2");
	else if (e->fract == 8)
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "8- Mandelbar V1");
	else
		mlx_string_put(e->mlx, e->win, 5, 340, 0XFFFFFF, "9- Mandelbar V2");
	mlx_string_put(e->mlx, e->win, 5, 360, 0XFFFFFF, "Zoom: +/-");
	mlx_string_put(e->mlx, e->win, 190, 360, 0XFFFFFF, "Iteration: 1/4");
	mlx_string_put(e->mlx, e->win, 5, 380, 0XFFFFFF, "Reset: 2");
	mlx_string_put(e->mlx, e->win, 190, 380, 0XFFFFFF, "Next: 3");
}
