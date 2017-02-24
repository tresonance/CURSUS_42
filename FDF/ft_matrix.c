/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 01:21:16 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 09:51:44 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix		*ft_translate(int tx, int ty, int tz)
{
	t_matrix	*m;

	m = init_matrix();
	m->a[3][0] = tx;
	m->a[3][1] = ty;
	m->a[3][2] = tz;
	m->a[0][0] = 1;
	m->a[1][1] = 1;
	m->a[2][2] = 1;
	return (m);
}

t_matrix		*ft_scale(double sx, double sy, double sz)
{
	t_matrix	*m;

	m = init_matrix();
	m->a[0][0] = sx;
	m->a[1][1] = sy;
	m->a[2][2] = sz;
	return (m);
}

t_matrix		*ft_rotate_z(double x)
{
	t_matrix	*m;

	m = init_matrix();
	m->a[0][0] = cos(x);
	m->a[1][0] = -sin(x);
	m->a[0][1] = sin(x);
	m->a[1][1] = cos(x);
	m->a[2][2] = (1.0);
	return (m);
}

t_matrix		*ft_rotate_y(double x)
{
	t_matrix	*m;

	m = init_matrix();
	m->a[0][0] = cos(x);
	m->a[2][0] = sin(x);
	m->a[0][2] = -sin(x);
	m->a[2][2] = cos(x);
	m->a[1][1] = 1.0;
	return (m);
}

t_matrix		*ft_rotate_x(double x)
{
	t_matrix	*m;

	m = init_matrix();
	m->a[1][1] = cos(x);
	m->a[1][2] = sin(x);
	m->a[2][1] = -sin(x);
	m->a[2][2] = cos(x);
	m->a[0][0] = 1.0;
	return (m);
}
