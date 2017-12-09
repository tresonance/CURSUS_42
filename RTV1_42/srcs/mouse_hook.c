/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 10:31:46 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/11 02:11:05 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int				search_inside(t_obj *obj)
{
	char		*name;
	int			i;

	i = -1;
	while (obj && obj->name[++i] && obj->name[i] == '\t')
		;
	name = &obj->name[i];
	if (ft_strcmp(name, "sphere") == 0)
		return (1);
	else if (ft_strcmp(name, "cylinder") == 0)
		return (1);
	else if (ft_strcmp(name, "cone") == 0)
		return (1);
	else if (ft_strcmp(name, "plane") == 0)
		return (1);
	else if (ft_strcmp(name, "light") == 0)
		return (0);
	return (0);
}
