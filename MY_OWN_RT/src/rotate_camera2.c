
#include "../includes/rt.h"
#define POS e->cam->pos
#define DIR e->cam->lookat

void		rotate_cam_pos(int key, t_env *e)
{
	if (key == ONE)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(-0.13),
			POS.x * sinf(0.13) + POS.y * cosf(0.13), POS.z};
	if (key == TWO)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(0.13),
			POS.x * sinf(-0.13) + POS.y * cosf(0.13), POS.z};
	if (key == FOUR)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(0.13), POS.y,
			POS.x * sinf(-0.13) + POS.z * cosf(0.13)};
	if (key == FIVE)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(-0.13),
			POS.y, POS.x * sinf(0.13) + POS.z * cosf(0.13)};
	if (key == SEVEN)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z *
			sinf(-0.13), POS.y * sinf(0.13) + POS.z * cosf(0.13)};
	if (key == HEIGHT)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z * sinf(0.13),
			POS.y * sinf(-0.13) + POS.z * cosf(0.13)};
}

void		rotate_cam_dir(int key, t_env *e)
{
	if (key == ONE)
		e->cam->lookat = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(-0.13),
			DIR.x * sinf(0.13) + DIR.y * cosf(0.13), DIR.z};
	if (key == TWO)
		e->cam->lookat = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(0.13),
			DIR.x * sinf(-0.13) + DIR.y * cosf(0.13), DIR.z};
	if (key == FOUR)
		e->cam->lookat = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y, DIR.x * sinf(-0.13) + DIR.z * cosf(0.13)};
	if (key == FIVE)
		e->cam->lookat = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(-0.13),
			DIR.y, DIR.x * sinf(0.13) + DIR.z * cosf(0.13)};
	if (key == SEVEN)
		e->cam->lookat = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z *
			sinf(-0.13), DIR.y * sinf(0.13) + DIR.z * cosf(0.13)};
	if (key == HEIGHT)
		e->cam->lookat = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y * sinf(-0.13) + DIR.z * cosf(0.13)};
}

void		rotate_camera(int key, t_env *e)
{
	rotate_cam_pos(key, e);
	rotate_cam_dir(key, e);
	//rotate_selected_obj_rot(key, e);
	init_camera_axes(e->cam);
}
