/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 04:46:52 by thchin            #+#    #+#             */
/*   Updated: 2017/04/22 03:11:27 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_matrix	identity_matrix(void)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		if (i == j)
			m.m[i][j] = 1.0;
		else
			m.m[i][j] = 0.0;
		j += 1;
		if (j > 3)
		{
			j = 0;
			i += 1;
		}
	}
	return (m);
}

t_matrix	translate_matrix(t_vector dir)
{
	t_matrix	m;

	m = identity_matrix();
	m.m[0][3] = dir.x;
	m.m[1][3] = dir.y;
	m.m[2][3] = dir.z;
	return (m);
}

t_matrix	rotate_matrix(t_vector dir, double angle)
{
	t_matrix	m;

	m.m[0][0] = dir.x * dir.x * (1.0 - cosf(angle)) + cosf(angle);
	m.m[0][1] = dir.x * dir.y * (1.0 - cosf(angle)) - dir.z * sinf(angle);
	m.m[0][2] = dir.x * dir.z * (1.0 - cosf(angle)) + dir.y * sinf(angle);
	m.m[0][3] = 0;
	m.m[1][0] = dir.y * dir.x * (1.0 - cosf(angle)) + dir.z * sinf(angle);
	m.m[1][1] = dir.y * dir.y * (1.0 - cosf(angle)) + cosf(angle);
	m.m[1][2] = dir.y * dir.z * (1.0 - cosf(angle)) - dir.x * sinf(angle);
	m.m[1][3] = 0;
	m.m[2][0] = dir.x * dir.z * (1.0 - cosf(angle)) - dir.y * sinf(angle);
	m.m[2][1] = dir.y * dir.z * (1.0 - cosf(angle)) + dir.x * sinf(angle);
	m.m[2][2] = dir.z * dir.z * (1.0 - cosf(angle)) + cosf(angle);
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1.0;
	return (m);
}

t_vector	matrix_mul_vect(t_matrix m, t_vector v)
{
	t_vector	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z +
		m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z +
		m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z +
		m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z +
		m.m[3][3] * v.w;
	return (result);
}
