/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:59:28 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 21:35:19 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

cl_float4		crossvect(cl_float4 v1, cl_float4 v2)
{
	cl_float4	v;

	v.s[0] = v1.s[1] * v2.s[2] - v1.s[2] * v2.s[1];
	v.s[1] = v1.s[2] * v2.s[0] - v1.s[0] * v2.s[2];
	v.s[2] = v1.s[0] * v2.s[1] - v1.s[1] * v2.s[0];
	v.s[3] = 0.0f;
	return (v);
}

cl_float4		scalevect(cl_float4 v1, float s)
{
	cl_float4	v;

	v.s[0] = v1.s[0] * s;
	v.s[1] = v1.s[1] * s;
	v.s[2] = v1.s[2] * s;
	v.s[3] = v1.s[3] * s;
	return (v);
}

float			dotproduct(cl_float4 v1, cl_float4 v2)
{
	float		tmp;

	tmp = v1.s[0] * v2.s[0] + v1.s[1] * v2.s[1] + v1.s[2] * v2.s[2];
	return (tmp);
}
