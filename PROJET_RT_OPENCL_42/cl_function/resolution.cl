#include "rt.cl.h"
#define PI 3.14159265358979323846264338327950288419716939937511

int		non_null_denominator(int num_sol, float *roots, int *choice_index)
{
	int i;

	if (num_sol == 0)
		return (0);
	i = -1;
	while(++i < num_sol)
	{
		if(roots[i] < -TOLERANCE || roots[i] > TOLERANCE)
		{
			*choice_index = i;
			return (1);
		}
	}
	return (0);
}


int	quadratic(t_poly poly, float *root)
{
	float	result[2];

	poly.a = 0.0f;
	poly.b = 0.0f;

	poly.delta = (poly.d * poly.d) - (4 * poly.c * poly.e);
	if (poly.delta < 0.0f)
		return (0);
	/*if(fabs(poly.delta) < (float)TOLERANCE)
	{
		*root = -poly.d / (2.0 * poly.c);
		return (1);
	}*/
	result[0] = (-poly.d + sqrtf(poly.delta)) / (2.0 * poly.c);
	result[1] = (-poly.d - sqrtf(poly.delta)) / (2.0 * poly.c);
	/*if (result[0] * result[1] <= 0.0f)
	{
		root[0] = (result[0] >= 0.0f) ? result[0] : result[1];
		return (1);
	}
	else if(result[0] >= 0.0f && result[1] >= 0.0f)
	{
		root[0] = (result[0] <= result[1]) ? result[0] : result[1];
		return(1);
	}*/
	return (2);
}

int		cubic(t_poly poly, float *roots)
{

	float sp;
	float teta;
	float d;
	float u;
	float v;

	if (poly.b >= -TOLERANCE && poly.b <= TOLERANCE)
		return (quadratic(poly, roots));
	poly.p = ((3.0f * poly.b * poly.d) - (poly.c * poly.c)) / (9.0f * poly.b * poly.b);
	poly.q = ((poly.c * poly.d) / (6.0f * poly.b * poly.b)) + (poly.c * poly.c * poly.c / (-27.0f * poly.b * poly.b * poly.b)) + (poly.e / (-2.0f * poly.b)) ;
	poly.r = poly.c / (-3.0f * poly.b);

	poly.delta = (poly.q * poly.q) + (poly.p * poly.p * poly.p);
	if (poly.delta <= 0.0f)
	{
		sp = sqrtf(-poly.p);
		teta = acos(poly.q / (sp * sp * sp)) / 3.0;
		d = 2.0 * sp;
		roots[0] = poly.r + d * cos(teta);
		roots[1] = poly.r + d * cos(teta + (PI * 2.0f /3.0f));
		roots[2] = poly.r + d * cos(teta + (PI * 4.0f / -3.0f));
		return (3);
	}
	else
	{
		poly.delta = sqrtf(poly.delta);
		poly.s = poly.q + poly.delta;
		poly.t = poly.q - poly.delta;
		u = (float)copysignf((float)powf((float)fabs(poly.s) , 0.333333333333333), poly.s);
		v = (float)copysignf((float)powf((float)fabs(poly.t) , 0.333333333333333), poly.t);
		roots[0] = poly.u + poly.v + poly.r;
		return (1);
	}
}

int		quartic(t_poly poly, float *roots)
{
	float sol[3];
	float sol1[2];
	float sol2[2];
	int num_sol[3];
	t_poly p;
	t_poly q;
	int i;

	if (poly.a >= - TOLERANCE &&  poly.a <= TOLERANCE)
		return (cubic(poly, roots));
	poly.p = poly.c /(2.0 * poly.a) - (3.0 * poly.b * poly.b) / (16.0 * poly.a * poly.a);
	poly.q = (poly.b * poly.c) / (2.0 * poly.a * poly.a) - poly.d / poly.a - (poly.b * poly.b * poly.b)/(8.0 * poly.a * poly.a * poly.a);
	poly.r = (3.0 * poly.b * poly.b * poly.b * poly.b) / (256.0 * poly.a * poly.a * poly.a * poly.a) - (poly.b * poly.b * poly.c) / (16.0 * poly.a * poly.a * poly.a) + (poly.d * poly.b) / (4.0 * poly.a * poly.a) - poly.e / poly.a;
	poly.s = poly.b / (-4.0 * poly.a);

	p = (t_poly){0.0,8.0, 16.0 * poly.p , 8.0 * ((poly.p * poly.p) + poly.r), -poly.q * poly.q, 0, 0, 0, 0 ,0 ,0, 0 ,0};
	num_sol[0] = cubic(p, sol);
	if (num_sol[0] == 0)
		return(0);
	else
	{
		if (0 == non_null_denominator(num_sol[0], sol, &i))
			return (0);
		
	}
	poly.t = sqrt(2.0 * sol[i]);

	p = (t_poly){0.0, 0.0, 1.0, poly.t, poly.p + sol[0] + (poly.t * poly.q) / (4.0 * sol[i]), 0, 0, 0, 0, 0, 0 , 0, 0};
	num_sol[1] = quadratic(p, sol1);

	q = (t_poly){0.0, 0.0, 1.0, -poly.t, poly.p + sol[0] - (poly.t * poly.q) / (4.0 * sol[i]), 0, 0, 0, 0, 0, 0, 0, 0};
	num_sol[2] = quadratic(q, sol2);
	roots[0] = sol1[0] + poly.s;
	roots[1] = sol1[1] + poly.s;
	roots[2] = sol2[0] + poly.s;
	roots[3] = sol2[1] + poly.s;
	return (num_sol[1] + num_sol[2]);
}

void	sort_float_tab(float *root, unsigned int size)
{
	unsigned int	i;
	float			temp;

	i = 0;
	while (i < (size - 1))
	{
		if (root[i] > root[i + 1])
		{
			temp = root[i];
			root[i] = root[i + 1];
			root[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

float			degre4_solver(t_prim prim, t_ray *ray )
{
	int i;
	int j;
	int num_sol;
	int swap;
	float tmp;
	float root[4];
	t_poly  poly;
	float4  dist;

	dist = ray->pos - prim.pos;
	/*poly.a = dot(ray->dir, ray->dir) * dot(ray->dir, ray->dir) ;

	poly.b = 4.0 * dot(ray->dir, ray->dir) *  dot(dist , ray->dir) ;

	poly.c = 2.0 * dot(ray->dir, ray->dir) * (dot(dist, dist) + (prim.pos1.x * prim.pos1.x) - (prim.pos1.y * prim.pos1.y)) + (2.0 * dot(dist, ray->dir) * 2.0 * dot(dist, ray->dir)) - (4.0 * prim.pos1.x * prim.pos1.x * (ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y));

	poly.d = 2.0 * 2.0 * dot(dist, ray->dir) * (dot(dist, dist) + prim.pos1.x * prim.pos1.x  - prim.pos1.y * prim.pos1.y) -  8.0 * (prim.pos1.x * prim.pos1.x) * (dist.x * ray->dir.x + dist.y * ray->dir.y);

	poly.e = powf((float)(dot(dist, dist) + (prim.pos1.x * prim.pos1.x) - (prim.pos1.y * prim.pos1.y)), 2) - 4.0 * prim.pos1.x * prim.pos1.x * (dist.x * dist.x + dist.y * dist.y);
*/
	 poly.a= 1.0;
poly.b = 4.0 * dot(dist, ray->dir);
poly.c = 2.0 * (dot(dist, dist) + prim.pos1.x * prim.pos1.x - prim.pos1.y * prim.pos1.y) + 0.25f * poly.b * poly.b - 4.0f * prim.pos1.x * prim.pos1.x * (1.0f - dot(prim.rot ,ray->dir) *  dot(prim.rot, ray->dir));
poly.d = poly.b * (dot(dist, dist) + prim.pos1.x * prim.pos1.x - prim.pos1.y * prim.pos1.y)- 4.0 * prim.pos1.x * prim.pos1.x * 2.0f * (dot(dist, ray->dir) - dot(prim.rot, dist) * dot(prim.rot, ray->dir));
poly.e = poly.e =  (dot(dist, dist) + prim.pos1.x * prim.pos1.x - prim.pos1.y * prim.pos1.y) *  (dot(dist, dist) + prim.pos1.x * prim.pos1.x - prim.pos1.y * prim.pos1.y) - 4.0 * prim.pos1.x * prim.pos1.x * (dot(dist, dist) - dot(prim.rot, dist) * dot(prim.rot, dist));
	num_sol = quartic(poly, root);
	if(0 == num_sol)
		return (-1.0f);
	sort_float_tab(&root[0], num_sol);
	i = -1;
	while (++i < num_sol)
	{
		if (root[i] > 0.0f)
			return (root[i]);
	}
	return (-1.0f);
}
