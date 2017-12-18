/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:59:42 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 16:16:19 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		err_exit(char *str)
{
        ft_putstr(str);
        exit(1);
}

int			err_exit2(char *str)
{
	ft_putstr_fd("!!! ERROR IN SCENE FILE !!!\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
	return (0);
}
void		ft_clamp_color(t_color *a, double min, double max)
{
	a->r = (a->r < min) ? min : a->r;
	a->g = (a->g < min) ? min : a->g;
	a->b = (a->b < min) ? min : a->b;

	a->r = (a->r > max) ? max : a->r;
	a->g = (a->r > max) ? max : a->g;
	a->b = (a->r > max) ? max : a->b;
}

void		set_inter_info1(t_hit **new, double t, t_vector normal, t_vector point)
{
	(*new)->t = t;
	(*new)->normal = normal;
	(*new)->point = point;
}

void		set_inter_info2(t_hit **new, t_obj **obj, t_ray ray, t_vector ray_origin)
{
	(*new)->obj = *obj;
	(*new)->in_ray = ray;
	(*new)->ray_origin = ray_origin;
	(*new)->next = NULL;
}

