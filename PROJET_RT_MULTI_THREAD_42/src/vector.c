/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 00:00:01 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 00:00:10 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

t_vector	subvect(t_vector u, t_vector v)
{
	return ((t_vector){u.x - v.x, u.y - v.y, u.z - v.z});
}

t_vector	addvect(t_vector u, t_vector v)
{
	return ((t_vector){u.x + v.x, u.y + v.y, u.z + v.z});
}

void		opposite(t_vector *v)
{
	v->x *= -1.0;
	v->y *= -1.0;
	v->z *= -1.0;
}

t_vector	scalevect(double a, t_vector v)
{
	return ((t_vector){a * v.x, a * v.y, a * v.z});
}

double		prodscal(t_vector u, t_vector v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vector	crossvect(t_vector u, t_vector v)
{
	return ((t_vector){u.y * v.z - u.z * v.y, v.x * u.z -v.z * u.x, u.x * v.y - u.y * v.x });
}

double		normevect(t_vector v)
{
	return (sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

double		normevectsquar(t_vector v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

}
void		normalize(t_vector *v)
{
	double m;

	m = normevect(*v);
	v->x /= m;
	v->y /= m;
	v->z /= m;
}

t_vector	add_bias(double bias, t_vector v)
{
	return ((t_vector){v.x + bias, v.y + bias, v.z + bias });
}
int		isnull_vector(t_vector v)
{
	return (fabs(v.x) < (double)EPSILON && fabs(v.y) < (double)EPSILON && fabs(v.z) < (double)EPSILON);   
}
