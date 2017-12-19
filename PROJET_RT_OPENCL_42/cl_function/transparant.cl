#include "rt.cl.h"

static void	add_transparant(t_ray ray, t_ray *stack, int *back_ray, int *queue,
						t_hit hit, t_obj hitobj)
{
	t_ray	new_ray;
	float	t;

	reflect(&new_ray, hit);
	new_ray.depth = ray.depth + 1;
	new_ray.color = ray.color * hitobj.prim.color * new_ray.depth;
	new_ray.kr = (float4)(1.0f - hitobj.mat.coef) * new_ray.color;
	push_ray(stack, new_ray, back_ray, queue);

	ray.pos = hit.point - hit.normal * 0.0001f;
	t = sphere_inter(hitobj.prim, &ray, 1);
	if (0.0001f < t && t < MAXRENDERDIST)
	{
		new_ray.pos = (ray.pos + ray.dir * t) +
						(normalize(ray.pos + ray.dir * t - hitobj.prim.pos) * 0.0001f);
		new_ray.dir = ray.dir;
		new_ray.depth = ray.depth + 1;
		new_ray.color = ray.color * exp(hitobj.prim.color * hitobj.mat.coef * t);
		new_ray.kr = new_ray.color;
		push_ray(stack, new_ray, back_ray, queue);
	}
	else
	{
		new_ray.pos = ray.pos;
		new_ray.dir = ray.dir;
		new_ray.depth = ray.depth + 1;
		new_ray.color = ray.color * exp(hitobj.prim.color * hitobj.mat.coef * hit.t);
		new_ray.kr = new_ray.color;
		push_ray(stack, new_ray, back_ray, queue);
	}
}
