#include "rt.cl.h"

static void	push_ray(t_ray *stack, t_ray ray, int *current, int *queue)
{
	if (*current >= MAX_RAY_COUNT)
		*current = 0;
	stack[*current] = ray;
	*current += 1;
	*queue += 1;
}

static void	pop_ray(t_ray *stack, t_ray *ray, int *current, int *queue)
{
	if (*current >= MAX_RAY_COUNT)
		*current = 0;
	*ray = stack[*current];
	*current += 1;
	*queue -= 1;
}

static void	current_ray(float x, float y, __global t_cam *cam, t_ray *ray)
{
	float	xindent;
	float	yindent;
	float	fov;

	fov = 45.0f;
	xindent = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * tan(fov / 2 * M_PI / 180) * ((float)WIDTH / HEIGHT);
	yindent = (1.0f - 2.0f * ((y + 0.5f) / HEIGHT)) * tan(fov / 2 * M_PI / 180);
	xindent *= -1.0f;
	ray->pos = cam->pos;
	ray->dir.x = FOC * cam->normal.x + yindent * cam->up.x + xindent * cam->right.x;
	ray->dir.y = FOC * cam->normal.y + yindent * cam->up.y + xindent * cam->right.y;
	ray->dir.z = FOC * cam->normal.z + yindent * cam->up.z + xindent * cam->right.z;
	ray->dir.w = 0.0;
	ray->dir = normalize(ray->dir);
	ray->depth = 0;
	ray->kr = (float4)(1.0f);
	ray->color = (float4)(1.0f);
}
