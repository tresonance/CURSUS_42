/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:46:25 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 15:53:24 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void		set_cubic_coef(t_polyn *poly)
{
	poly->p = ((3.0 * poly->b * poly->d) - (poly->c * poly->c)) /
		(9.0 * poly->b * poly->b);
	poly->q = ((poly->c * poly->d) / (6.0 * poly->b * poly->b)) +
		(poly->c * poly->c * poly->c / (-27.0 * poly->b * poly->b * poly->b)) +
		(poly->e / (-2.0 * poly->b));
	poly->r = poly->c / (-3.0 * poly->b);
}

static void		set_complex_roots(t_polyn poly, double d, double teta,
		double *roots)
{
	roots[0] = poly.r + d * cos(teta);
	roots[1] = poly.r + d * cos(teta + (PI * 2.0 / 3.0));
	roots[2] = poly.r + d * cos(teta + (PI * 4.0 / -3.0));
}

static void		set_real_coef(t_polyn *poly)
{
	poly->delta = sqrtf(poly->delta);
	poly->s = poly->q + poly->delta;
	poly->t = poly->q - poly->delta;
	poly->u = copysign(pow(fabs(poly->s), 1.0 / 3.0), poly->s);
	poly->v = copysign(pow(fabs(poly->t), 1.0 / 3.0), poly->t);
}

int				cubic(t_polyn poly, double roots[])
{
	double		sp;
	double		teta;
	double		d;

	if (fabs(poly.b) < (double)TOLERANCE)
		return (quadratic(poly, roots));
	set_cubic_coef(&poly);
	poly.delta = (poly.q * poly.q) + (poly.p * poly.p * poly.p);
	if (poly.delta <= 0.0)
	{
		sp = sqrtf(-poly.p);
		teta = acos(poly.q / (sp * sp * sp)) / 3.0;
		d = 2.0 * sp;
		set_complex_roots(poly, d, teta, &roots[0]);
		return (3);
	}
	else
	{
		set_real_coef(&poly);
		roots[0] = poly.u + poly.v + poly.r;
		return (1);
	}
	return (0);
}
