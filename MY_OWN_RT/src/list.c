/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:51:48 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 01:26:39 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		add_point_to_intersection_list(t_hit **hit, t_hit *new)
{
	t_hit *tmp;
	
	if (!*hit)
		*hit = new;
	else
	{
		tmp = *hit;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int		ft_list_size(t_hit *lst)
{
	t_hit *tmp;
	int count;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void		cameralist_from_objlist(t_hit *hit, t_cam cam)
{
	t_hit *tmp;
	
	tmp = hit;
	while (tmp)
	{//ceux ki doivent etre ramené a camera space
		if (ft_strcmp(tmp->obj->name ,"\tplane") && ft_strcmp(tmp->obj->name, "\ttriangle"))
	
		{
			tmp->point = camerapoint_from_objpoint(tmp->point, cam, tmp->obj->center);
			tmp->normal = cameradir_from_objdir(tmp->normal, cam);
		}
		tmp = tmp->next;
	}
}

void		copy_hit(t_hit **inter, t_hit *hit)
{
	if (!(*inter = (t_hit*)malloc(sizeof(t_hit))))
		err_exit("unabale to allocate hit inter\n");
	(*inter)->t = hit->t;
	(*inter)->point = hit->point;
	(*inter)->normal = hit->normal;
	(*inter)->obj = hit->obj;
}

int		pickclosest_intersection(t_hit *hit_list, t_hit **inter, t_cam cam)
{
	int list_size;
	t_hit	*closest;
	t_hit *tmp;
	int	count;
	double diff;
	//int ans;

	list_size = ft_list_size(hit_list);
	cameralist_from_objlist(hit_list, cam);
	if (0 == list_size)
		return(0);
	else if (1 == list_size)
	{
		//if (hit_list->displacement > (double)INFINI)
		//	return (0);
	//	binary_object_intersection(hit_list, inter, cam);
		copy_hit(inter, hit_list);
		/*if(0 == binary_object_operation(hit_list, inter, cam))
		{
			destroy_intersection_list(&hit_list);
			free(*inter);
			return (0);
		}*/
		destroy_intersection_list(&hit_list);
		return (1);
	}
	else
	{
			closest = hit_list;;
			tmp = hit_list;
			count = 1;
			while (tmp->next)
			{ 
				diff = tmp->next->displacement - closest->displacement;
				if (fabs(diff) < (double)EPSILON)
					count++;
				else if (diff < 0.0)
				{
					closest = tmp->next;
					count = 1;
				}
				tmp = tmp->next;
			}
		//if (closest->displacement < (double)EPSILON)
		//	return (0);
			copy_hit(inter, closest);
			if(0 == binary_object_operation(hit_list, inter, cam))
			{
				destroy_intersection_list(&hit_list);
				free(*inter);
				return (0);
			}
			destroy_intersection_list(&hit_list);
	}
	return (count);
}



int		is_hit_point_already_inside(t_vector p, t_hit *hit_list)
{
	t_hit *tmp;

	tmp = hit_list;
	double dx;
	double dy;
	double dz;

	while (tmp)
	{
		dx = fabs(tmp->point.x - p.x);
		dy = fabs(tmp->point.y - p.y);
		dz = fabs(tmp->point.z - p.z);
		if (dx < (double)EPSILON && dy < (double)EPSILON && dz < (double)EPSILON)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void		append_solid_intersection(t_obj *tmp, t_ray ray, t_hit **hit_list)
{
	if (!ft_strcmp(tmp->name, "\tcuboid"))
		append_cuboid(tmp, ray, hit_list);

	if (!ft_strcmp(tmp->name, "\tsphere"))
	  	append_sphere(tmp, ray, hit_list);

	  /*if (!ft_strcmp(tmp->name, "\tspheroid"))
	  	append_spheroid(tmp, ray, hit_list);*/

	  if (!ft_strcmp(tmp->name, "\tcylinder"))
	  	append_cylinder(tmp, ray, hit_list);

	  if (!ft_strcmp(tmp->name, "\tcone"))
	 	append_cone(tmp, ray, hit_list);
	  if (!ft_strcmp(tmp->name, "\tplane"))
	  	append_plane(tmp, ray, hit_list);
	
	 if (!ft_strcmp(tmp->name, "\tblock"))
	  	append_block(tmp, ray, hit_list);

	  if (!ft_strcmp(tmp->name, "\tbrick"))
	  	append_brick(tmp, ray, hit_list);
	  if (!ft_strcmp(tmp->name, "\ttriangle"))
	  	append_triangle(tmp, ray, hit_list);

	  if (!ft_strcmp(tmp->name, "\tchessboard"))
	  	append_chessboard(tmp, ray, hit_list);
		
	   if (!ft_strcmp(tmp->name, "\tthinring"))
			append_thinring(tmp, ray, hit_list);

	  if (!ft_strcmp(tmp->name, "\ttorus"))
			append_torus(tmp, ray, hit_list);
		if (!ft_strcmp(tmp->name, "\tmobius"))
			append_mobius(tmp, ray, hit_list);
	if (!ft_strcmp(tmp->name, "\tbox"))
			append_box(tmp, ray, hit_list);
}

void		ft_list_merge(t_hit **begin_list1, t_hit **begin_list2)
{
	t_hit *tmp;

	if (!*begin_list1)
		*begin_list1 = *begin_list2;
	else
	{
		tmp = *begin_list1;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = *begin_list2;
	}
	destroy_intersection_list(begin_list2);
}

void		brick(t_obj *obj_list, t_hit **hit_list);

void		append_all_intersection(t_obj *obj, t_ray ray, t_hit **hit_list)
{
	t_obj *tmp;
	
	tmp = obj;
	while (tmp)
	{
		append_solid_intersection(tmp, ray, hit_list);
		tmp = tmp->next;
	}
	//brick(obj,  hit_list);
}

int	findclosest_intersection(t_env *e, t_ray ray, t_hit **inter)
{
	t_hit *hit_list;

	hit_list = NULL; 
	append_all_intersection(e->scene->obj, ray, &hit_list);
	//if (hit_list && hit_list->obj->csg_operator != 0)
	//	binary_object_intersection(&hit_list);
	//block(e->scene->obj, &hit_list); 

	return (pickclosest_intersection(hit_list, inter, *e->cam));
}


//POINT INSIDE SOLID OR NOT

int		is_point_inside_this_obj(t_obj *obj, t_vector point)
{
	t_ray ray;
	int entercount;
	int exitcount;
	t_hit *hit_list;
	t_hit *tmp_hit;
	

	ray.pos = point;
	ray.dir = (t_vector){0.0, 1.0, 0.0};
	hit_list = NULL;

	append_solid_intersection(obj, ray,  &hit_list);

	tmp_hit = hit_list;
	exitcount = 0;
	entercount = 0;
	
	while (tmp_hit)
	{
		if (tmp_hit->obj->enclosed == TRUE/* && !ft_strcmp(tmp_hit->obj->name, obj->name)*/)
		{
			if (prodscal(tmp_hit->normal, ray.dir) > 0.0f)
				++exitcount;
			else if (prodscal(tmp_hit->normal, ray.dir) < 0.0f)
				++entercount;
		}
		tmp_hit = tmp_hit->next;
	}
	if (hit_list)
		destroy_intersection_list(&hit_list);
	if (exitcount - entercount == 1)
		return (TRUE);

	return (FALSE);
}

// IF POINT IS INSIDE AN OBJECT WHICH OBJECT IN THE SCENE ?

t_obj		*hit_obj(t_obj *obj, t_vector point)
{
	t_obj  *tmp;

	tmp = obj;
	
	while (tmp)
	{
		if (TRUE == is_point_inside_this_obj(tmp, point))
			return(tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

