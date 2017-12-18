/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 23:14:05 by ibtraore          #+#    #+#             */
/*   Updated: 2017/12/14 23:15:03 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			move_primect(t_scene *scene)
{
	cl_float4	q;
	float		angle;

	angle = 5.0f * M_PI / 180 / 2 * scene->frametime;
	q.s[0] = 0.0f;
	q.s[1] = -0.6f * sin(angle);
	q.s[2] = 0.0f;
	q.s[3] = cos(angle);
	scene->prim[0].pos = subvect(scene->prim[0].pos, scene->prim[1].pos);
	scene->prim[0].pos = hamilton_product(q, scene->prim[0].pos);
	scene->prim[0].pos = hamilton_product(scene->prim[0].pos, conjugate(q));
	scene->prim[0].pos = addvect(scene->prim[0].pos, scene->prim[1].pos);
	scene->prim[2].pos = subvect(scene->prim[2].pos, scene->prim[1].pos);
	scene->prim[2].pos = hamilton_product(q, scene->prim[2].pos);
	scene->prim[2].pos = hamilton_product(scene->prim[2].pos, conjugate(q));
	scene->prim[2].pos = addvect(scene->prim[2].pos, scene->prim[1].pos);
	angle = 50.0f * M_PI / 180 / 2 * scene->frametime;
	q.s[1] = 1.0f * sin(angle);
	q.s[0] = -0.4f * sin(angle);
	scene->prim[0].pos = subvect(scene->prim[0].pos, scene->prim[2].pos);
	scene->prim[0].pos = hamilton_product(q, scene->prim[0].pos);
	scene->prim[0].pos = hamilton_product(scene->prim[0].pos, conjugate(q));
	scene->prim[0].pos = addvect(scene->prim[0].pos, scene->prim[2].pos);
	clEnqueueWriteBuffer(scene->cl.command_queue, scene->cl.prim, CL_TRUE, 0,
			3 * sizeof(t_prim), scene->prim, 0, NULL, NULL);
}
