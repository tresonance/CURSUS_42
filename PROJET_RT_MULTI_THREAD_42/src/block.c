/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:41:31 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 11:40:26 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		append_block(t_obj *block, t_ray ray, t_hit **hit_list)
{
	append_cuboid(block, ray, hit_list);
}

t_color		get_block_texture_color(t_hit *inter, t_env *e)
{
	return (get_cuboid_texture_color(inter, e));
}
