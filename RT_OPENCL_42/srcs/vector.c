/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:59:28 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 21:34:47 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

cl_float4		conjugate(cl_float4 v1)
{
	cl_float4	v;

	v.s[0] = v1.s[0] * -1.0f;
	v.s[1] = v1.s[1] * -1.0f;
	v.s[2] = v1.s[2] * -1.0f;
	v.s[3] = v1.s[3];
	return (v);
}

cl_float4		hamilton_product(cl_float4 v1, cl_float4 v2)
{
	cl_float4	v;

	v.s[3] = v1.s[3] * v2.s[3] - v1.s[0] * v2.s[0] - v1.s[1] * v2.s[1] -
		v1.s[2] * v2.s[2];
	v.s[0] = v1.s[3] * v2.s[0] + v1.s[0] * v2.s[3] + v1.s[1] * v2.s[2] -
		v1.s[2] * v2.s[1];
	v.s[1] = v1.s[3] * v2.s[1] - v1.s[0] * v2.s[2] + v1.s[1] * v2.s[3] +
		v1.s[2] * v2.s[0];
	v.s[2] = v1.s[3] * v2.s[2] + v1.s[0] * v2.s[1] - v1.s[1] * v2.s[0] +
		v1.s[2] * v2.s[3];
	return (v);
}

cl_float4		addvect(cl_float4 v1, cl_float4 v2)
{
	cl_float4	v;

	v.s[0] = v1.s[0] + v2.s[0];
	v.s[1] = v1.s[1] + v2.s[1];
	v.s[2] = v1.s[2] + v2.s[2];
	v.s[3] = v1.s[3] + v2.s[3];
	return (v);
}

cl_float4		subvect(cl_float4 v1, cl_float4 v2)
{
	cl_float4	v;

	v.s[0] = v1.s[0] - v2.s[0];
	v.s[1] = v1.s[1] - v2.s[1];
	v.s[2] = v1.s[2] - v2.s[2];
	v.s[3] = v1.s[3] - v2.s[3];
	return (v);
}

cl_float4		normalize(cl_float4 v)
{
	float		length;

	length = 1.0f / sqrtf(v.s[0] * v.s[0] + v.s[1] * v.s[1] +
							v.s[2] * v.s[2]);
	v.s[0] = v.s[0] * length;
	v.s[1] = v.s[1] * length;
	v.s[2] = v.s[2] * length;
	v.s[3] = 0.0f;
	return (v);
}
