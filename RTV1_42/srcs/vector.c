/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 07:42:37 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:16:20 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_vector	subvect(t_vector *v1, t_vector *v2)
{
	t_vector	v;

	v.x = v2->x - v1->x;
	v.y = v2->y - v1->y;
	v.z = v2->z - v1->z;
	v.w = 0.0;
	return (v);
}

t_vector	addvect(t_vector *v1, t_vector *v2)
{
	t_vector	v;

	v.x = v2->x + v1->x;
	v.y = v2->y + v1->y;
	v.z = v2->z + v1->z;
	v.w = 0.0;
	return (v);
}

t_vector	scalevect(double k, t_vector *v1)
{
	t_vector	v;

	v.x = k * v1->x;
	v.y = k * v1->y;
	v.z = k * v1->z;
	v.w = 1.0;
	return (v);
}

float		normevect(t_vector *v1)
{
	float			ret;

	ret = (v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z);
	ret = sqrtf(ret);
	return (ret);
}

t_vector	crossvect(t_vector *v1, t_vector *v2)
{
	t_vector	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v2->x * v1->z - v2->z * v1->x;
	v.z = v1->x * v2->y - v1->y * v2->x;
	v.w = 0.0;
	return (v);
}
