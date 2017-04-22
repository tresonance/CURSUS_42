/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 07:51:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:03:20 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int		key_hook(int key, t_env *e)
{
	if (key == ESCAPE)
		clear_env(e);
	if (key == C)
		e->aa *= 2;
	if (key == V)
		e->aa /= 2;
	e->aa = (e->aa < 1) ? 1 : e->aa;
	translate(key, e);
	rotate(key, e);
	rotate_n_axis(key, e);
	draw_obj(e);
	return (0);
}
