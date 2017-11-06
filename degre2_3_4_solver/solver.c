
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define TOLERANCE 1.0e-6

int		quadratic(double a, double b, double c, double *roots)
{
	double delta;

	if (fabs(a) < (double)TOLERANCE)
	{
		if (fabs(b) < (double)TOLERANCE)
			return (0);
		else
		{
			roots[0] = -c / b;
			return (1);
		}
		return (0);
	}
	delta = (b * b) - (4 * a * c);
	if (delta < (double)(-TOLERANCE))
		return (0);
	if(fabs(delta) < (double)TOLERANCE)
	{
		roots[0] = -b / (2.0 * a);
		roots[1] = roots[0];
		return (2);
	}
	roots[0] = (-b + sqrtf(delta)) / (2.0 * a);
	roots[1] = (-b - sqrtf(delta)) / (2.0 * a);
	return (2);
}

int				cubic(double a, double b, double c, double d, double  roots[])
{
	double p;
	double q;
	double w1;
	double w2;
	double u;
	double v;
	double t;
	double delta;
	double		sign;

	if (fabs(a) <= (double)TOLERANCE)
		return (quadratic(b, c, d, &roots[0]));
	p = -b*b / (3.0 * a*a) + c/a;
	q = ((2.0 * b * b * b) / (27.0 * a*a*a)) - ((b*c)/(3.0 * a * a)) + d/a;
	if(fabs(p) <= (double)TOLERANCE)
	{
		roots[0] = powf(-q, 1.0/3.0) - b /(3.0 * a);
		return (1);
	}
	if (fabs(q) <= (double)TOLERANCE && fabs(p) > (double)TOLERANCE)
	{
		if(p < (double)(-TOLERANCE))
		{
			roots[0] = 0.0;
			roots[1] = sqrtf(p);
			roots[2] = -1.0 * sqrtf(p);
			return(3);
		}
		else
		{
			roots[0] = 0.0;
			return (1);
		}
	}
	delta = (q * q / 4.0)  + (p * p * p / 27.0);
	if (delta > (double)TOLERANCE)
	{
		sign = ((-q/2.0  + sqrtf(delta)) < 0.0) ? -1.0 : 1.0;
		w1 = pow(fabs(-q/2.0 + sqrtf(delta)), 1.0/3.0);
		w1 *= sign;
		sign = ((-q/2.0  - sqrtf(delta)) < 0.0) ? -1.0 : 1.0;
		w2 = pow(fabs(-q/2.0 - sqrtf(delta)), 1.0/3.0);
		w2 *= sign;

		roots[0] = w1 + w2 - b/(3.0 * a);
		return (1);
	}
	else if (fabs(delta) <= (double)TOLERANCE)
	{
		roots[0] = (3.0 * q)/p - b/(3.0 * a);
		roots[1] = ((-3.0 * q) / (2.0 * p)) - b/(3.0 * a);
		roots[2] = roots[1];
		return(3);
	}
	else
	{
		u = 2.0 * sqrtf(-p/3.0);
		//v = -q/(2.0 * copysign(pow(fabs(-p/3.0), 3/2), -p/3.0));
		v = -q/(2.0 * pow(-p/3.0, 3.0/2.0));
		t = acos(v)/3.0;
		roots[0] = u * cos(t) - b/(3*a); 
		roots[1] = u * cos(t + (2.0 * M_PI/3.0)) - b/(3*a);
		roots[2] = u * cos(t + (4.0 * M_PI/3.0)) - b/(3*a);
		return (3);
	}
}

int			quartic(double a, double b, double c, double d, double e, double *roots)
{
	double p;
	double q;
	double r;
	double y[4];
	int num_sol[2];
	double a0;
	double b0;
	int i;
	int j;

	if(fabs(a) < (double)TOLERANCE)
		return(cubic(b, c, d, e, &roots[0]));
	p = -3.0 * b*b/(8.0 * a*a) + c/a;
	q = b*b*b/(8.0*a*a*a) - b*c/(2.0*a*a) + d/a;
	r = -3*b*b*b*b/(256.0*a*a*a*a) + c*b*b/(16.0*a*a*a) - b*d/(4.0*a*a)  + e/a;
	if(fabs(p) <= (double)TOLERANCE)
	{
		if (fabs(q) <= (double)TOLERANCE)
		{
			if (r > 0.0)
				return (0);
			else
			{
				roots[0] = -sqrtf(-r);
				roots[1] = sqrtf(-r);
				return (2);
			}
		}
	}
	if (fabs(q) <= (double)TOLERANCE)
	{
		num_sol[0] = quadratic(1.0, p, r, &y[0]);
		i = -1;
		j = 0;
		while(++i < num_sol[0])
		{
			if (y[i] > 0.0)
			{
				roots[j++] = sqrtf(y[i]);
				roots[j++] = -sqrtf(y[i]);
			}
			if (i == num_sol[0])
				return(j);
		}
	}
	num_sol[0] = cubic(8.0, -4.0*p, -8.0*r, 4.0*r*p - q*q, &y[0]);
	if (0 == num_sol[0])
		return (0);
	if (-p + 2.0 * y[0] < 0.0)
		return (0);
	a0 = sqrtf(-p + 2.0 * y[0]);
	//b0 = (fabs(a0) <= (double)TOLERANCE) ? sqrtf(y[0]*y[0] - r) : sqrtf(-q/(2.0*a0));
	//num_sol[0] = quadratic(1.0, a0, y[0]+b0, &roots[0]);
	num_sol[0] = quadratic(1.0, a0, y[0] - q/(2.0*a0), &roots[0]);
	i = -1;
	while(++i < num_sol[0])
		roots[i] -= b/(4.0 * a);
	//num_sol[1] = quadratic(1.0, a0, y[0]+b0, &roots[num_sol[0]]);
	num_sol[1] = quadratic(1.0, -a0, y[0] + q/(2.0 * a0), &roots[num_sol[0]]);
	i = -1;
	while(++i < num_sol[1])
		roots[num_sol[0] + i] -= b/(4.0 * a);
	return(num_sol[0] + num_sol[1]);
}

int			main(int argc, char **argv)
{
	double a;
	double b;
	double c;
	double d;
	double e;
	double roots[4];
	int num;
	int i;

	if (argc == 6)
	{
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		c = atoi(argv[3]);
		d = atoi(argv[4]);
		e = atoi(argv[5]);
		num = quartic(a, b, c, d, e, &roots[0]);
		i = -1;
		while (++i < num)
			printf("roots[%d] = %lf\n", i, roots[i]);
	}
	else
		printf("Error: Parameter number\n");
	return (0);
}
