/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 03:55:02 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/05 13:11:46 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void		normalize(t_vector *v1)
{
	double	norm;

	norm = 1.0 / sqrtf(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z);
	v1->x = v1->x * norm;
	v1->y = v1->y * norm;
	v1->z = v1->z * norm;
	v1->w = 0.0;
}

double		prodscal(t_vector *v1, t_vector *v2)
{
	double	ret;

	ret = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (ret);
}

t_vector	opposite(t_vector *v)
{
	t_vector	n;

	n.x = -1.0 * v->x;
	n.y = -1.0 * v->y;
	n.z = -1.0 * v->z;
	n.w = v->w;
	return (n);
}

double		ft_clamp(double value, int a, int b)
{
	value = (value > b) ? b : value;
	value = (value < a) ? a : value;
	return (value);
}
