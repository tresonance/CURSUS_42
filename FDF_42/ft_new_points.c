/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:08:26 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 12:06:02 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix			*init_matrix(void)
{
	t_matrix		*m;
	int				i;
	int				j;

	if (!(m = (t_matrix*)malloc(sizeof(t_matrix))))
		ft_err_exit("Unable to allocate");
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m->a[i][j] = 0.0;
	}
	m->a[3][3] = 1.0;
	return (m);
}

void				new_point(t_point *p, t_matrix *m, t_env *e)
{
	t_point			q;

	p->x -= e->xcenter;
	p->y -= e->ycenter;
	q.x = p->x;
	q.y = p->y;
	q.z = p->z;
	q.w = p->w;
	p->x = (q.x * m->a[0][0]) + (q.y * m->a[1][0]) + (q.z * m->a[2][0]) +
		(q.w * m->a[3][0]);
	p->y = (q.x * m->a[0][1]) + (q.y * m->a[1][1]) + (q.z * m->a[2][1]) +
		(q.w * m->a[3][1]);
	p->z = (q.x * m->a[0][2]) + (q.y * m->a[1][2]) + (q.z * m->a[2][2]) +
		(q.w * m->a[3][2]);
	p->x += e->xcenter;
	p->y += e->ycenter;
}

void				all_points(t_env *e, t_matrix *m)
{
	int				i;
	int				j;

	i = -1;
	while (++i < e->line)
	{
		j = -1;
		while (++j < e->col)
			new_point(e->map->lines[i]->points[j], m, e);
	}
	e->xcenter = (e->map->lines[e->line - 1]->points[e->col - 1]->x +
			e->map->lines[0]->points[0]->x) / 2;
	e->ycenter = (e->map->lines[e->line - 1]->points[e->col - 1]->y +
			e->map->lines[0]->points[0]->y) / 2;
}

void				isometric_representation(t_env *e)
{
	int				i;
	int				j;
	t_point			p;
	t_point			q;

	i = -1;
	e->xstart = WIDTH / 3;
	e->ystart = HEIGHT / 4;
	e->zoom = (int)WIDTH / (e->col * e->col);
	e->zoom = (e->zoom == 0) ? 3 : e->zoom;
	e->m = ft_scale(e->zoom, e->zoom, 1);
	all_points(e, e->m);
	free(e->m);
	while (++i < e->line)
	{
		j = -1;
		while (++j < e->col)
		{
			p = *e->map->lines[i]->points[j];
			q.x = e->xstart + (p.x - p.y);
			q.y = e->ystart + (p.x + p.y) - p.z;
			e->map->lines[i]->points[j]->x = q.x;
			e->map->lines[i]->points[j]->y = q.y;
		}
	}
}

void				set_isometric_function(t_env *e)
{
	isometric_representation(e);
	e->xcenter = (e->map->lines[e->line - 1]->points[e->col - 1]->x +
			e->map->lines[0]->points[0]->x) / 2;
	e->ycenter = (e->map->lines[e->line - 1]->points[e->col - 1]->y +
			e->map->lines[0]->points[0]->y) / 2;
}
