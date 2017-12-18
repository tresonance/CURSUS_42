/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 04:31:40 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 05:25:28 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_grad(float gradient2[8][2])
{
	float unit;

	unit = 1.0f / sqrt(2);
	gradient2[0][0] = unit;
	gradient2[0][1] = unit;
	gradient2[1][0] = -unit;
	gradient2[1][1] = unit;
	gradient2[2][0] = unit;
	gradient2[2][1] = -unit;
	gradient2[3][0] = -unit;
	gradient2[3][1] = -unit;
	gradient2[4][0] = 1;
	gradient2[4][1] = 0;
	gradient2[5][0] = -1;
	gradient2[5][1] = 0;
	gradient2[6][0] = 0;
	gradient2[6][1] = 1;
	gradient2[7][0] = 0;
	gradient2[7][1] = -1;
}

t_noise			get_grad(unsigned int perm[512], int x, int y)
{
	int		ii;
	int		jj;
	t_noise	n;

	n.x0 = (int)(x);
	n.y0 = (int)(y);
	ii = n.x0 & 255;
	jj = n.y0 & 255;
	n.gi0 = perm[ii + perm[jj]] % 8;
	n.gi1 = perm[ii + 1 + perm[jj]] % 8;
	n.gi2 = perm[ii + perm[jj + 1]] % 8;
	n.gi3 = perm[ii + 1 + perm[jj + 1]] % 8;
	return (n);
}

float			noise2d(unsigned int perm[512], float x, float y)
{
	t_noise	n;
	float	gradient2[8][2];

	init_grad(gradient2);
	n = get_grad(perm, x, y);
	n.tmpx = x - n.x0;
	n.tmpy = y - n.y0;
	n.s = gradient2[n.gi0][0] * n.tmpx + gradient2[n.gi0][1] * n.tmpy;
	n.tmpx = x - (n.x0 + 1);
	n.tmpy = y - n.y0;
	n.t = gradient2[n.gi1][0] * n.tmpx + gradient2[n.gi1][1] * n.tmpy;
	n.tmpx = x - n.x0;
	n.tmpy = y - (n.y0 + 1);
	n.u = gradient2[n.gi2][0] * n.tmpx + gradient2[n.gi2][1] * n.tmpy;
	n.tmpx = x - (n.x0 + 1);
	n.tmpy = y - (n.y0 + 1);
	n.v = gradient2[n.gi3][0] * n.tmpx + gradient2[n.gi3][1] * n.tmpy;
	n.tmp = x - n.x0;
	n.cx = 3 * n.tmp * n.tmp - 2 * n.tmp * n.tmp * n.tmp;
	n.li1 = n.s + n.cx * (n.t - n.s);
	n.li2 = n.u + n.cx * (n.v - n.u);
	n.tmp = y - n.y0;
	n.cy = 3 * n.tmp * n.tmp - 2 * n.tmp * n.tmp * n.tmp;
	return (n.li1 + n.cy * (n.li2 - n.li1));
}

float			turbulence(unsigned int perm[512], float x, float y, float res)
{
	float	initial_res;
	float	value;

	initial_res = res;
	value = 0.0f;
	while (res >= 1)
	{
		value += noise2d(perm, x / res, y / res) * res;
		res /= 2.0f;
	}
	return (value / initial_res);
}
