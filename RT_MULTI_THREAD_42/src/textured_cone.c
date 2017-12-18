/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:23:29 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 15:23:36 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_color		get_cone_texture_color(t_hit *inter, t_env *e)
{
	return (get_sphere_texture_color(inter, e));
}
