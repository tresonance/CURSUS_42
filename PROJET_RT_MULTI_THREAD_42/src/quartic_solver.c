/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartic_solver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:54:13 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:54:21 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"


int		non_null_denominator(int num_sol, double roots[], int *choice_index)
{
	int i;

	if (num_sol == 0)
		return (0);
	i = -1;
	while(++i < num_sol)
	{
		if(fabs(roots[i]) > (double)TOLERANCE)
		{
			*choice_index = i;
			return (1);
		}
	}
	return (0);
}

int			quartic(t_polyn poly, double roots[])
{
	double sol[3];
	double sol1[3];
	double sol2[3];
	int num_sol[3];
	t_polyn p;
	t_polyn q;
	int i;

	if (fabs(poly.a) < (double)TOLERANCE)
		return (cubic(poly, roots));
	poly.p = poly.c /(2.0 * poly.a) - (3.0 * poly.b * poly.b) / (16.0 * poly.a * poly.a);
	poly.q = (poly.b * poly.c) / (2.0 * poly.a * poly.a) - poly.d / poly.a - (poly.b * poly.b * poly.b)/(8.0 * poly.a * poly.a * poly.a);
	poly.r = (3.0 * poly.b * poly.b * poly.b * poly.b) / (256.0 * poly.a * poly.a * poly.a * poly.a) - (poly.b * poly.b * poly.c) / (16.0 * poly.a * poly.a * poly.a) + (poly.d * poly.b) / (4.0 * poly.a * poly.a) - poly.e / poly.a;
	poly.s = poly.b / (-4.0 * poly.a);

	p = (t_polyn){0.0,8.0, 16.0 * poly.p , 8.0 * ((poly.p * poly.p) + poly.r), -poly.q * poly.q, 0, 0, 0, 0 ,0 ,0, 0 ,0};
	num_sol[0] = cubic(p, sol);
	if (num_sol[0] == 0)
		return(0);
	else
	{
		if (0 == non_null_denominator(num_sol[0], sol, &i))
			return (0);
	}
	poly.t = sqrt(2.0 * sol[i]);

	p = (t_polyn){0.0, 0.0, 1.0, poly.t, poly.p + sol[0] + (poly.t * poly.q) / (4.0 * sol[i]), 0, 0, 0, 0, 0, 0 , 0, 0};
	num_sol[1] = quadratic(p, sol1); 

	q = (t_polyn){0.0, 0.0, 1.0, -poly.t, poly.p + sol[0] - (poly.t * poly.q) / (4.0 * sol[i]), 0, 0, 0, 0, 0, 0, 0, 0};
	num_sol[2] = quadratic(q, sol2); 
	roots[0] = sol1[0] + poly.s;
	roots[1] = sol1[1] + poly.s;
	roots[2] = sol2[0] + poly.s;
	roots[3] = sol2[1] + poly.s;
	return (num_sol[1] + num_sol[2]);
}
