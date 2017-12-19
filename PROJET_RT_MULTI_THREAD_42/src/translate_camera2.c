
#include "../includes/rt.h"

void	translate_cam_pos(int key, t_env *e)
{
	t_vector pos;

	pos = e->cam->pos;
	if (key == RIGHT)
		e->cam->pos = (t_vector){pos.x + e->cam->right.x * 10.0, pos.y + e->cam->right.y * 10.0,
			pos.z + e->cam->right.z * 10.0};
	else if (key == LEFT)
		e->cam->pos = (t_vector){pos.x - e->cam->right.x * 10.0, pos.y - e->cam->right.y * 10.0,
			pos.z - e->cam->right.z * 10.0};
	else if (key == UP)
		e->cam->pos = (t_vector){pos.x + e->cam->up.x * 10.0, pos.y + e->cam->up.y * 10.0,
			pos.z + e->cam->up.z * 10.0};
	else if (key == DOWN)
		e->cam->pos = (t_vector){pos.x - e->cam->up.x * 10.0, pos.y - e->cam->up.y * 10.0,
			pos.z - e->cam->up.z * 10.0};
	else if (key == PLUS)
		e->cam->pos = (t_vector){pos.x + e->cam->dir.x * 10.0, pos.y + e->cam->dir.y * 10.0, pos.z +
			e->cam->dir.z * 10.0};
	else if (key == MINUS)
		e->cam->pos = (t_vector){pos.x - e->cam->dir.x * 10.0, pos.y - e->cam->dir.y * 10.0, pos.z -
			e->cam->dir.z * 10.0};
}

void	translate_cam_lookat(int key, t_env *e)
{
	t_vector pos;

	pos = e->cam->lookat;
	if (key == RIGHT)
		e->cam->lookat = (t_vector){pos.x + e->cam->right.x * 10.0, pos.y + e->cam->right.y * 10.0,
			pos.z + e->cam->right.z * 10.0};
	else if (key == LEFT)
		e->cam->lookat = (t_vector){pos.x - e->cam->right.x * 10.0, pos.y - e->cam->right.y * 10.0,
			pos.z - e->cam->right.z * 10.0};
	else if (key == UP)
		e->cam->lookat = (t_vector){pos.x + e->cam->up.x * 10.0, pos.y + e->cam->up.y * 10.0,
			pos.z + e->cam->up.z * 10.0};
	else if (key == DOWN)
		e->cam->lookat = (t_vector){pos.x - e->cam->up.x * 10.0, pos.y - e->cam->up.y * 10.0,
			pos.z - e->cam->up.z * 10.0};
	else if (key == PLUS)
		e->cam->lookat = (t_vector){pos.x + e->cam->dir.x * 10.0, pos.y + e->cam->dir.y * 10.0, pos.z +
			e->cam->dir.z * 10.0};
	else if (key == MINUS)
		e->cam->lookat = (t_vector){pos.x - e->cam->dir.x * 10.0, pos.y - e->cam->dir.y * 10.0, pos.z -
			e->cam->dir.z * 10.0};
}


void	translate_camera(int key, t_env *e)
{
	init_camera_axes(e->cam);
	translate_cam_pos(key, e);
	//translate_cam_lookat(key, e);
	//init_camera_axes(e->cam);
}
