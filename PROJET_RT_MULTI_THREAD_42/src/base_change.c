/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:39:43 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 11:34:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vector		objectdir_from_cameradir(t_vector dir_in_cam_space, t_base base)
{
	t_vector	dir_in_obj_space;

	dir_in_obj_space.x = prodscal(dir_in_cam_space, base.rdir);
	dir_in_obj_space.y = prodscal(dir_in_cam_space, base.sdir);
	dir_in_obj_space.z = prodscal(dir_in_cam_space, base.tdir);
	return (dir_in_obj_space);
}

t_vector		objectpoint_from_camerapoint(t_vector point_in_cam_space,
		t_vector objcenter, t_base objbase)
{
	t_vector	tr;

	tr = subvect(point_in_cam_space, objcenter);
	return (objectdir_from_cameradir(tr, objbase));
}

t_vector		cameradir_from_objdir(t_vector dir_in_objspace, t_cam cam)
{
	t_vector	dir_in_cam_space;

	dir_in_cam_space.x = prodscal(dir_in_objspace, cam.right);
	dir_in_cam_space.y = prodscal(dir_in_objspace, cam.up);
	dir_in_cam_space.z = prodscal(dir_in_objspace, cam.dir);
	return (dir_in_cam_space);
}

t_vector		camerapoint_from_objpoint(t_vector point_in_obj_space,
		t_cam cam, t_vector objcenter)
{
	t_vector	res;

	res = cameradir_from_objdir(point_in_obj_space, cam);
	res.x += objcenter.x;
	res.y += objcenter.y;
	res.z += objcenter.z;
	return (res);
}
