/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 02:40:29 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 23:16:17 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	update_time(t_scene *scene)
{
	scene->old_time = scene->time;
	scene->time = SDL_GetTicks();
	scene->accumtime += (scene->time - scene->old_time);
	scene->frametime = (scene->time - scene->old_time) / 1000.0;
}
