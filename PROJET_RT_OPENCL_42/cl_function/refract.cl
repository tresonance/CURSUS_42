#include "rt.cl.h"

static int		refract(t_ray *ray, t_hit hit, float ior)
{
	float	cosi;
	float	etai;
	float	etat;
	float	eta;
	float	k;
	float4	n;

	cosi = clamp(dot(hit.ray_origin.dir, hit.normal), -1.0f, 1.0f);
	n = hit.normal;
	if (cosi < 0)
	{
		etai = 1.0f;
		etat = ior;
		cosi = -cosi;
	}
	else
	{
		etai = ior;
		etat = 1.0f;
		n *= -1.0f;
	}
	eta = etai / etat;
	k = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (k >= 0)
	{
		ray->dir = hit.ray_origin.dir * eta + n * (eta * cosi - sqrt(k));
		ray->dir = normalize(ray->dir);
		ray->pos = hit.point - n * 0.001f;
		return (1);
	}
	return (0);
}

static float	fresnel(t_hit hit, float ior)
{
	float	r;
	float	kr;
	float	cosi;

	cosi = fabs(dot(hit.ray_origin.dir, hit.normal));
	r = (1.0f - ior) / (1.0f + ior);
	r = r * r;
	kr = r + (1.0f - r) * pow(1.0f - cosi, 5);
	return (kr);
}

static void	add_refract(t_ray ray, t_ray *stack, int *back_ray, int *queue,
					t_hit hit, float4 tmp_color, t_obj hitobj)
{
	t_ray	new_ray;
	bool	outside;
	float	kr;

	kr = fresnel(hit, 1.3);
	outside = dot(hit.ray_origin.dir, hit.normal) < 0;
	if (kr < 1.0f && 1 == refract(&new_ray, hit, 1.3f))
	{
		new_ray.depth = ray.depth + 1;
		new_ray.color = ray.color * hitobj.prim.color;
		new_ray.kr = ((float4)1.0f - kr);
		push_ray(stack, new_ray, back_ray, queue);
	}
	reflect(&new_ray, hit);
	new_ray.pos = outside ? hit.point + hit.normal * 0.001f : hit.point - hit.normal * 0.001f;
	new_ray.depth = ray.depth + 1;
	new_ray.color = ray.color * hitobj.prim.color * new_ray.depth;
	new_ray.kr = new_ray.color;
	push_ray(stack, new_ray, back_ray, queue);
}
