/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:38:15 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/11 01:41:13 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int				close_win(t_env *e)
{
	(void)e->mlx.mlx;
	exit(0);
	return (0);
}

void			free_list(t_list **list)
{
	t_list *tmp;

	if (*list)
	{
		while (*list)
		{
			tmp = *list;
			*list = tmp->next;
			free(tmp->content);
			free(tmp);
		}
	}
}

void			clear_env(t_env **env)
{
	if (*env)
	{
		(*env)->mlx.img ? mlx_destroy_image((*env)->mlx.mlx,
			(*env)->mlx.img) : 0;
		(*env)->mlx.win ? free((*env)->mlx.win) : 0;
		(*env)->mlx.mlx ? free((*env)->mlx.mlx) : 0;
		if ((*env)->obj)
			free_list(&((*env)->obj));
		if (*env)
		{
			(*env)->cam ? free((*env)->cam) : 0;
			free(*env);
		}
	}
	exit(0);
}
