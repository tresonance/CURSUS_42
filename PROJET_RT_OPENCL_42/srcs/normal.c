/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:54:33 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 06:50:42 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	*create_perlin(unsigned int perm[512], t_image *data, int size)
{
	int			x;
	int			y;
	float		value;
	cl_float4	*pmap;

	x = 0;
	y = 0;
	pmap = (cl_float4 *)malloc(data->width * data->height * sizeof(cl_float4));
	if (NULL == pmap)
		return (NULL);
	while (y < data->height)
	{
		value = turbulence(perm, x, y, size);
		pmap[y * data->width + x].s[0] = (value + 1) * 0.5f;
		pmap[y * data->width + x].s[1] = (value + 1) * 0.5f;
		pmap[y * data->width + x].s[2] = (value + 1) * 0.5f;
		x += 1;
		if (x >= data->width)
		{
			x = 0;
			y += 1;
		}
	}
	return (pmap);
}

cl_float4	*create_marble(unsigned int perm[512], t_image *data, t_marble m)
{
	int			x;
	int			y;
	float		value;
	cl_float4	*pmap;

	x = 0;
	y = 0;
	pmap = (cl_float4 *)malloc(data->width * data->height * sizeof(cl_float4));
	if (NULL == pmap)
		return (NULL);
	while (y < data->height)
	{
		value = sin(x * m.xperiod / data->width + y * m.yperiod / data->height +
				m.turbpower * turbulence(perm, x, y, m.turbsize) * M_PI) * -1;
		pmap[y * data->width + x].s[0] = (value + 1) * 0.5f;
		pmap[y * data->width + x].s[1] = (value + 1) * 0.5f;
		pmap[y * data->width + x].s[2] = (value + 1) * 0.5f;
		x += 1;
		if (x >= data->width)
		{
			x = 0;
			y += 1;
		}
	}
	return (pmap);
}

cl_float4	get_clampedpos(cl_float4 *map, int x, int y, t_image *data)
{
	if (x < 0)
		x = 0;
	if (x >= data->width)
		x = data->width - 1;
	if (y < 0)
		y = 0;
	if (y >= data->height)
		y = data->height - 1;
	return (map[y * data->width + x]);
}

cl_float4	snobel(int x, int y, t_image *data, cl_float4 *pmap)
{
	t_bump		b;
	cl_float4	tmp;

	tmp = get_clampedpos(pmap, x + 1, y - 1, data);
	b.tl = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x + 1, y, data);
	b.l = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x + 1, y + 1, data);
	b.bl = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x, y + 1, data);
	b.b = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x - 1, y + 1, data);
	b.br = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x - 1, y, data);
	b.r = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x - 1, y - 1, data);
	b.tr = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp = get_clampedpos(pmap, x, y - 1, data);
	b.t = (tmp.s[0] + tmp.s[1] + tmp.s[2]) / 3;
	tmp.s[0] = (b.r - b.l) * 2.0f + b.tr + b.br - b.tl - b.bl;
	tmp.s[1] = (b.b - b.t) * 2.0f + b.br + b.bl - b.tr - b.tl;
	tmp.s[2] = 1.0f / 10.0f;
	tmp.s[3] = 0;
	return (tmp);
}

cl_float4	*conv_normalmap(t_image *data, cl_float4 *pmap)
{
	int			x;
	int			y;
	cl_float4	tmp;
	cl_float4	*nmap;

	nmap = (cl_float4 *)malloc(data->width * data->height * sizeof(cl_float4));
	if (NULL == nmap)
		return (NULL);
	x = 0;
	y = 0;
	while (y < data->height)
	{
		tmp = snobel(x, y, data, pmap);
		nmap[y * data->width + x] = normalize(tmp);
		x += 1;
		if (x >= data->width)
		{
			x = 0;
			y += 1;
		}
	}
	return (nmap);
}
