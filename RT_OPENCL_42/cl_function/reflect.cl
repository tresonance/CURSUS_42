#include "rt.cl.h"

static void	reflect(t_ray *ray, t_hit hit)
{
	ray->dir = hit.ray_origin.dir -
				hit.normal * 2.0f * dot(hit.ray_origin.dir, hit.normal);
	ray->dir = normalize(ray->dir);
	ray->pos = hit.point + hit.normal * 0.001f;
}

static void	add_reflect(t_ray ray, t_ray *stack, int *back_ray, int *queue,
					t_hit hit, float4 tmp_color)
{
	t_ray	new_ray;

	reflect(&new_ray, hit);
	new_ray.depth = ray.depth + 1;
	new_ray.color = ray.color * tmp_color * new_ray.depth;
	new_ray.kr = new_ray.color;
	push_ray(stack, new_ray, back_ray, queue);
}
