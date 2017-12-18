
#include "../includes/rt.h"
#define PLANE_TILE_DIM 17
#define TILE_DIM 3
#define SCALE_S 5
#define SCALE_T 5
#define VIS 10

float		modulo(const float x)
{
	return (x - floor(x));
}

t_color		get_procedural_texture_color(t_hit *inter)
{
	int parite1;
	int parite2;
	int parite3;
	int deno;

	deno = (ft_strcmp(inter->obj->name, "\tplane") == 0) ? (double)PLANE_TILE_DIM : (double)TILE_DIM;
	//deno = (double)TILE_DIM;
	parite1 = inter->point.x / deno;
	parite2 = inter->point.y / deno;
	parite3 = inter->point.z / deno;
	if (parite3 % 2 == 0)
	{
		if ((parite1 % 2 == 0 && parite2 % 2 == 0)
		|| (parite1 % 2 == 1 && parite2 % 2 == 1))
			return ((t_color){0.0, 0.0, 0.0});
		else
			return ((t_color){1.0, 1.0, 1.0});
	}
	else
	{
		if ((parite1 % 2 == 0 && parite2 % 2 == 0)
		|| (parite1 % 2 == 1 && parite2 % 2 == 1))
			return ((t_color){1.0, 1.0, 1.0});
		else
			return ((t_color){0.0, 0.0, 0.0});
	}
}

t_color		get_procedural_texture_color2(t_hit *inter)
{
	float pattern;

	pattern = (modulo(inter->point.x * SCALE_S) < 0.5) ^  (modulo(inter->point.y * SCALE_T) < 0.5);
	return((t_color){pattern, pattern, pattern });
}

