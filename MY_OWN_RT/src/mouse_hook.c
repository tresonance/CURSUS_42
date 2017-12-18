/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 03:33:59 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 07:16:52 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			expose_hook_func(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0,0);
	return (0);
}

int			close_win(t_env *e)
{
	(void)e->mlx;
	exit(0);
	return (0);
}
