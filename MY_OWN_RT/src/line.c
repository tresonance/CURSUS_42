#include "../includes/rt.h"


void	slope_of_current_line(t_env *e, t_vector *point1, t_vector *point2)
{
	e->dx = fabs(point1->x - point2->x);
	e->flagdx = point1->x < point2->x ? 1 : -1;
	e->dy = fabs(point1->y - point2->y);
	e->flagdy = point1->y < point2->y ? 1 : -1;
	e->flag = (e->dx > e->dy ? e->dx : -e->dy) * 0.5;
}

void	set_pixel(t_vector *p, int color, t_env *e)
{
	int index;

	if ((int)p->x >= 0 && (int)p->x <= WIDTH && (int)p->y >= 0
			&& (int)p->y < HEIGHT)
	{
		index = ((int)p->y * e->sl) + ((int)p->x * e->bpp / 8);
		e->data[index] = color;
		e->data[++index] = color >> 8;
		e->data[++index] = color >> 16;
		e->data[++index] = color >> 24;
	}
}

int		valid_point(t_vector *point1)
{
	if (point1->x >= 0.0  &&  point1->x < WIDTH && point1->y < HEIGHT &&  point1->y >= 0)
		return (1);
	return (0);
}

void	line_loop(t_env *e, t_vector p0, t_vector  p1)
{
	double	val;
	int		booll;
	t_vector point;

	booll = 1;
	while (booll == 1 && !((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y))
	{
		if (valid_point(&p0) == 1)
		{
			point = p0;
			point.x = 0.5 * (p0.x + WIDTH);
			point.y = 0.5 * (-p0.y + HEIGHT);
			set_pixel(&point, 1677214, e);
			//set_pixel(&p0, ft_color_palette(p0, p0), e);
		}
		val = e->flag;
		booll = 0;
		if (val > -e->dx && (int)p0.x != (int)p1.x)
		{
			e->flag -= e->dy;
			p0.x += e->flagdx;
			booll = 1;
		}
		if (val < e->dy && (int)p0.y != (int)p1.y)
		{
			e->flag += e->dx;
			p0.y += e->flagdy;
			booll = 1;
		}
	}
}

void	line(t_env *e, t_vector p0, t_vector p1)
{
	if (valid_point(&p0) && valid_point(&p1))
	{
		slope_of_current_line(e, &p0, &p1);
		line_loop(e, p0, p1);
	}
}
