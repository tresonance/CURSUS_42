/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:42:25 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 12:44:13 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		menu(void)
{
	ft_putstr("WELCOME TO RT\n");
	ft_putstr("---------------\n\n");
	ft_putstr(">>>Translate objet<<<\n");
	ft_putstr("   ^   \n");
	ft_putstr("<     >\n");
	ft_putstr("   V   \n");
	ft_putstr(">>>Rotate objet<<<\n");
	ft_putstr("1-2, 4-5, 7-8\n\n");
	ft_putstr("Move first light : Q W E D S A\n");
	ft_putstr("Move second light : U I O L J K\n");
	ft_putstr("Anti aliasing : V C B \n");
	ft_putstr("left click : select objet\n");
	ft_putstr("R : stop selecting objet\n");
	ft_putstr("ESC : Quit\n");
}

int			cam_hook(int key, t_env *e)
{
	if (key == ESC)
		clear_env(&e);
	if (key == V)
		e->aa *= 2;
	if (key == C)
		e->aa /= 2;
	e->aa = (e->aa < 1) ? 1 : e->aa;
	if (key == B)
		e->aa = 1;
	printf("[key = %d]\n", key);
	rotate_camera(key, e);
	translate_light(key, e);
	translate_camera(key, e);
	all_thread_render(e);
	return (0);
}
