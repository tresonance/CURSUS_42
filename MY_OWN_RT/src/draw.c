/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:47:50 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 14:53:40 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		pixel_put(int x, int y, t_color color, t_env *e)
{
	int		index;
	int		col[3];

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		col[0] = (int)(255.0 * color.r);
		col[1] = (int)(255.0 * color.g);
		col[2] = (int)(255.0 * color.b);
		index = y * e->sl + (x * (e->bpp / 8));
		e->data[index] = *((char*)&col[2]);
		e->data[++index] = *((char*)&col[1]);
		e->data[++index] = *((char*)&col[0]);
	}
}
