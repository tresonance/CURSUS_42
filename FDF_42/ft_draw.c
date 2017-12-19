/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 01:59:07 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 09:25:52 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_env(t_env *e)
{
	e->bpp = BPP;
	e->line = 0;
	e->col = 0;
	e->endian = 0;
	e->zoom = WIDTH / 60;
	e->xcenter = 0;
	e->ycenter = 0;
	e->xstart = 0;
	e->ystart = 0;
}

void		ft_draw_line(t_env *e)
{
	int		i;
	int		j;
	t_point p;

	i = -1;
	while (++i < e->line - 1)
	{
		j = -1;
		while (++j < e->col - 1)
		{
			p = *e->map->lines[i]->points[j];
			if (e->map->lines[i]->points[j + 1])
				line(e, *e->map->lines[i]->points[j],
						*e->map->lines[i]->points[j + 1]);
			if (e->map->lines[i]->points[j])
				line(e, *e->map->lines[i]->points[j],
						*e->map->lines[i + 1]->points[j]);
		}
	}
	line(e, *(e->map->lines[0]->points[e->col - 1]),
			*(e->map->lines[e->line - 1]->points[e->col - 1]));
	line(e, *(e->map->lines[e->line - 1]->points[0]),
			*(e->map->lines[e->line - 1]->points[e->col - 1]));
}

void		set_image(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH + 100, HEIGHT + 100);
	e->pixel = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line),
			&(e->endian));
	ft_draw_line(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->pixel);
}
