/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:38:15 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:02:06 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	clear_env(t_env *env)
{
	t_list	*tmp;

	mlx_destroy_image(env->mlx.mlx, env->mlx.img);
	free(env->mlx.win);
	free(env->mlx.mlx);
	while (env->obj)
	{
		tmp = env->obj;
		env->obj = tmp->next;
		free(((t_obj*)tmp->content)->name);
		free(tmp->content);
		free(tmp);
	}
	exit(1);
}
