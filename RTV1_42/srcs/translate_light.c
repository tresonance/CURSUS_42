/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:49:03 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/13 11:26:21 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	translate_light_1(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj	light;

	if (e->light[0] == NULL)
		return ;
	light = *e->light[0];
	if (key == W)
		e->light[0]->pos = (t_vector){light.pos.x + r.x * 10.0,
			light.pos.y + r.y * 10.0, light.pos.z + r.z * 10.0, 1.0};
	else if (key == Q)
		e->light[0]->pos = (t_vector){light.pos.x - r.x * 10.0,
			light.pos.y - r.y * 10.0, light.pos.z - r.z * 10.0, 1.0};
	else if (key == E)
		e->light[0]->pos = (t_vector){light.pos.x + e->up.x * 10.0,
			light.pos.y + e->up.y * 10.0, light.pos.z + e->up.z * 10.0, 1.0};
	else if (key == D)
		e->light[0]->pos = (t_vector){light.pos.x - e->up.x * 10.0,
			light.pos.y - e->up.y * 10.0, light.pos.z - e->up.z * 10.0, 1.0};
	else if (key == A)
		e->light[0]->pos = (t_vector){light.pos.x + n.x * 10.0,
			light.pos.y + n.y * 10.0, light.pos.z + n.z * 10.0, 1.0};
	else if (key == S)
		e->light[0]->pos = (t_vector){light.pos.x - n.x * 10.0,
			light.pos.y - n.y * 10.0, light.pos.z - n.z * 10.0, 1.0};
}

void	translate_light_2(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj light;

	if (e->light[1] == NULL)
		return ;
	light = *e->light[1];
	if (key == O)
		e->light[1]->pos = (t_vector){light.pos.x + r.x * 10.0,
			light.pos.y + r.y * 10.0, light.pos.z + r.z * 10.0, 1.0};
	else if (key == I)
		e->light[1]->pos = (t_vector){light.pos.x - r.x * 10.0,
			light.pos.y - r.y * 10.0, light.pos.z - r.z * 10.0, 1.0};
	else if (key == U)
		e->light[1]->pos = (t_vector){light.pos.x + e->up.x * 10.0,
			light.pos.y + e->up.y * 10.0, light.pos.z + e->up.z * 10.0, 1.0};
	else if (key == J)
		e->light[1]->pos = (t_vector){light.pos.x - e->up.x * 10.0,
			light.pos.y - e->up.y * 10.0, light.pos.z - e->up.z * 10.0, 1.0};
	else if (key == K)
		e->light[1]->pos = (t_vector){light.pos.x + n.x * 10.0,
			light.pos.y + n.y * 10.0, light.pos.z + n.z * 10.0, 1.0};
	else if (key == L)
		e->light[1]->pos = (t_vector){light.pos.x - n.x * 10.0,
			light.pos.y - n.y * 10.0, light.pos.z - n.z * 10.0, 1.0};
}

void	translate_light(int key, t_vector r, t_vector n, t_env *e)
{
	translate_light_1(key, r, n, e);
	translate_light_2(key, r, n, e);
}
