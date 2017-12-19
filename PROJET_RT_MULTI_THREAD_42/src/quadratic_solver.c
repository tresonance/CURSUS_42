/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:53:50 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:54:00 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"


int		quadratic(t_polyn poly, double result[])
{
	poly.a = 0.0;
	poly.b = 0.0;

	if (fabs(poly.c) < (double)TOLERANCE)
	{
		if (fabs(poly.d) < (double)TOLERANCE)
			return (0);
		result[0] = -poly.e / poly.d;
		return (1);
	}
	poly.delta = (poly.d * poly.d) - (4 * poly.c * poly.e);
	if (poly.delta < 0.0)
		return (0);
	if(fabs(poly.delta) < (double)TOLERANCE)
	{
		result[0] = -poly.d / (2.0 * poly.c);
		result[1] = result[0];
		return (1);
	}
	result[0] = (-poly.d + sqrtf(poly.delta)) / (2.0 * poly.c);
	result[1] = (-poly.d - sqrtf(poly.delta)) / (2.0 * poly.c);
	return (2);
}

static void		combined_list_ordored(t_obj **obj, double *result, int num_sol)
{
	if(1 == num_sol)
	{
		(*obj)->tmin = result[0];
		(*obj)->tmax = result[0] + TOLERANCE;;
	}
	if(2 == num_sol)
	{
		if (result[0] * result[1] > 0.0f && result[0] >= 0.0f)
		{
				(*obj)->tmin = (result[0] < result[1]) ? result[0] : result[1];
				(*obj)->tmax = (result[0] < result[1]) ? result[1] : result[0];
		}
			else
			{
				(*obj)->tmax = (result[0] > 0.0f) ? result[0] : result[1];
				(*obj)->tmin = (result[0] > 0.0f) ? result[0] : result[1];
			}
	}
}

double		cut_obj(double *coef, t_obj *obj, t_vector rdir, t_vector rpos)
{
	int num_sol;
	double t_in;
	double t_out;
	double dc;
	double dw;
	double result[2];
	double t;

	num_sol = second_degre(&coef[0], result);
	combined_list_ordored(&obj, result, num_sol);
		if(num_sol == 0)
			return (-1.0);
		if (num_sol == 1)
			return(result[0]);

		if(obj->cut_flag == 0)
		{
			if (result[0] * result[1] > 0.0f)
				return(result[0] < result[1] ? result[0] : result[1]);
			else
				return(result[0] > 0.0f ? result[0] : result[1]);
		}
		else
		{
		t_in = (result[0] < result[1]) ? result[0] : result[1];
		t_out = (result[1] > result[0]) ? result[1] : result[0];
		}
	//obj->cut_axe = objectdir_from_cameradir(obj->cut_axe, obj->base);
	//obj->cut_axe = objectdir_from_cameradir(obj->cut_axe, obj->base);
		normalize(&obj->cut_axe);
		dc = prodscal(obj->cut_axe, rdir);
	//obj->cut_point  = objectpoint_from_camerapoint(obj->cut_point, obj->center,obj->base);
		dw = prodscal(subvect(rpos, obj->cut_point), obj->cut_axe);
		if(dc >-TOLERANCE && dc < TOLERANCE)
		{
			if (dw > TOLERANCE)
				return (-1.0);
		}
		else
		{
			t = -dw / dc;
			if(dc >= TOLERANCE)
			{
				if (t > t_in && t < t_out)
					t_out = t;
				else if(t < t_in)
					return(-1.0f);
			}
			else
			{
				if (t > t_in && t < t_out)
					t_in = t;
				else if(t > t_out)
					return(-1.0f);
			}
	}
	if(t_in > t_out)
		return(-1.0f);
	return(t_in);
}


