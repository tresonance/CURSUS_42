/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:56:06 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 02:15:12 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"


t_ray		reflect(t_hit *inter, t_ray ray)
{
	t_ray refl;
	double prod;
	t_vector scal;

	normalize(&ray.dir);
	prod = prodscal(ray.dir, inter->normal);
	scal = scalevect(2.0 * prod, inter->normal);
	//normalize(&scal);
	refl.dir = subvect(ray.dir, scal);
	normalize(&refl.dir);
	//refl.pos = inter->point;
	refl.type = REFLECTION_RAY;
	refl.obj_from = inter->obj;
	return (refl);
}

