/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:56:28 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 02:13:18 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		fresnel(t_hit *inter,  t_ray ray, t_env *e)
{
	float rs;
	float rp;

	//e->etai = (ray.type == PRIMARY_RAY) ? 1.0 : ray.obj_from->refractive_index;;
	if (ray.type == PRIMARY_RAY || ray.obj_from == NULL)
	e->etai = 1.0;
	else 
		e->etai = inter->obj->refractive_index;
	e->etat = inter->obj->refractive_index;
	e->cos_i = prodscal(ray.dir, inter->normal);
	ft_clamp_val(&e->cos_i, -1.0, 1.0);
	if (e->cos_i > 0.0)
		ft_swapf(&e->etai, &e->etat);
	e->sin_t = (e->etai / e->etat) * sqrtf(ft_maxf(0.0, 1.0 - (e->cos_i * e->cos_i)));	
	if (e->sin_t >= 1.0)
		e->kr = 1.0;
	else
	{
		e->cos_t = sqrtf(ft_maxf(0.0, 1.0 - (e->sin_t * e->sin_t)));
		e->cos_i = fabs(e->cos_i);
		rs = ((e->etat * e->cos_i) - (e->etai * e->cos_t)) / ((e->etat * e->cos_i) + (e->etai * e->cos_t));
		rp = ((e->etai * e->cos_i) - (e->etat * e->cos_t)) / ((e->etai * e->cos_i) + (e->etat * e->cos_t));
		e->kr = ((rs * rs) + (rp * rp)) / 2.0;
	}
}

t_ray		refract(t_hit *inter, t_ray ray, t_env *e)
{
	float k;
	t_vector left;
	t_vector right;
	t_ray	refr;
	t_ray	null;
	t_vector copy_normal;
	double eta;

	copy_normal = inter->normal;
	null.dir = (t_vector){0.0, 0.0, 0.0};
	e->cos_i = prodscal(ray.dir, inter->normal);
	ft_clamp_val(&e->cos_i, -1.0, 1.0);
	e->etai = (ray.type == PRIMARY_RAY) ? 1.0 : ray.obj_from->refractive_index;;
	e->etat = inter->obj->refractive_index;
	if (e->cos_i < 0.0)
	{
		opposite(&copy_normal);
	}
	else
	{
		ft_swapf(&e->etai, &e->etat);
		//opposite(&copy_normal);
	}
	eta = e->etai /  e->etat;
	//e->cos_i = fabs(e->cos_i);
	k = 1.0 - ((eta * eta) * (1.0 - (e->cos_i * e->cos_i)));
	if (k < 0.0)
		return (null);
	left = scalevect(eta, ray.dir);
	//normalize(&left);
	right = scalevect((eta * e->cos_i) - sqrtf(k), copy_normal);
	//normalize(&right);
	//refr.dir = addvect(left, right);
	refr.dir = addvect(left, right);
	normalize(&refr.dir);
	refr.type = REFRACTION_RAY;
	refr.obj_from = inter->obj;
	return (refr); 
}
