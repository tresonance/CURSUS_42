/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:06:51 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/07 22:16:14 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				fractale_man2(t_env *e, float tmp, float rz, float iz)
{
	e->x = -1;
	while (++e->x < X)
	{
		e->y = 0;
		while (++e->y < Y)
		{
			e->rc = e->x / e->zoom + e->xmin;
			e->ic = e->y / e->zoom + e->ymin;
			e->rz = 0;
			e->iz = 0;
			e->iter_index = 0;
			while (e->iter_index < e->iter_max && e->rz * e->rz +
					e->iz * e->iz < 4)
			{
				tmp = e->rz;
				rz = e->rz * e->rz;
				iz = e->iz * e->iz;
				e->rz = rz * e->rz - 3 * e->rz * iz + e->rc;
				e->iz = 3 * rz * e->iz - iz * e->iz + e->ic;
				e->iter_index++;
			}
			put_pixel(e->x, e->y, e);
		}
	}
}

void				fractale_man4(t_env *e, float tmp, float rz, float iz)
{
	e->x = -1;
	while (++e->x < X)
	{
		e->y = 0;
		while (++e->y < Y)
		{
			e->rc = e->x / e->zoom + e->xmin;
			e->ic = e->y / e->zoom + e->ymin;
			e->rz = 0;
			e->iz = 0;
			e->iter_index = 0;
			while (e->iter_index < e->iter_max && e->rz * e->rz +
					e->iz * e->iz < 4)
			{
				tmp = e->rz;
				rz = tmp * tmp;
				iz = e->iz * e->iz;
				e->rz = rz * rz - 6 * rz * iz + iz * iz + e->rc;
				e->iz = 4 * rz * tmp * e->iz - 4 * tmp * iz * e->iz + e->ic;
				e->iter_index++;
			}
			put_pixel(e->x, e->y, e);
		}
	}
}
