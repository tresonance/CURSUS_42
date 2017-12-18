#include "rt.h"

typedef t_vector (*ptrf)(t_obj*, t_vector, double, t_ray);

void sorted_insert(t_hit** head_ref, t_hit* new_node)
{
		t_hit* current;
	
		if (*head_ref == NULL || (*head_ref)->t >= new_node->t)
		{
			new_node->next = *head_ref;
			*head_ref = new_node;
		}
		else
		{
			current = *head_ref;
			while (current->next!=NULL && current->next->t < new_node->t)
			{
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
		}
}


void insertion_sort(t_hit **head_ref)
{
	t_hit *sorted;
	t_hit *current;
	t_hit *next;

	sorted = NULL;
	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		sorted_insert(&sorted, current);
		current = next;
	}
	*head_ref = sorted;
}

void		delete_first_node_in_hit_list(t_hit **hit_list)
{
	t_hit	*tmp;

	tmp = *hit_list;
	if(tmp)
	{
		tmp = tmp->next;
		free(*hit_list);
		*hit_list = tmp;
	}
}


void		convert_list_to_array(t_hit **hit_list, t_hit **arr)
{
	int len;
	int i;
	t_hit *tmp;

	i = -1;
	len = ft_list_size(*hit_list);
	if (!(*arr = (t_hit*)malloc(len * sizeof(t_hit))))
		err_exit("Unable to allocate list array");
	tmp = *hit_list;
	while(++i < len)
	{
		(*arr)[++i] = *tmp;
		tmp = tmp->next;
	}
}

void		insert_first(t_hit **hit_list, t_hit **new)
{

			(*new)->next = *hit_list;
			*hit_list = *new;
}

int		binary_object_union(t_hit *hit_list, t_hit **inter, t_cam cam)
{
	t_hit *tmp;
	t_vector point;

	if (1 == binary_object_intersection(hit_list, inter, cam) && inter)
		return (0);
	return (1);

	tmp = hit_list;
	while (tmp && tmp->next)
	{
		point = camerapoint_from_objpoint((*inter)->point, cam, (*inter)->obj->center);
		if (!is_point_inside_this_obj(tmp->obj, point) && inter)
			return (0);
		tmp  = tmp->next;
	}
	return (1);
}

int		binary_object_intersection(t_hit *hit_list, t_hit **inter, t_cam cam)
{
	t_hit *tmp;
	t_vector point;

	tmp = hit_list;
	while (tmp && tmp->next)
	{
		point = camerapoint_from_objpoint((*inter)->point, cam, (*inter)->obj->center);
		//point = add_bias(BIAS, point);

		if (!is_point_inside_this_obj(tmp->obj, point) && is_point_inside_this_obj(tmp->next->obj, point))
			tmp  = tmp->next;
		else
			return (0);
	}
	return (1);
	if (1 == binary_object_union(hit_list, inter, cam) && inter)
		return (0);
	return (1);
}

int		binary_object_difference(t_hit *hit_list, t_hit **inter, t_cam cam)
{
	t_hit *tmp;
	t_vector point;

	tmp = hit_list;
	while (tmp && tmp->next)
	{
		point = camerapoint_from_objpoint((*inter)->point, cam, (*inter)->obj->center);
		if (is_point_inside_this_obj(tmp->obj, point) && inter && !is_point_inside_this_obj(tmp->next->obj, point))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			binary_object_operation(t_hit *hit_list, t_hit **inter, t_cam cam)
{
		if (!hit_list->obj->csg_operator)
			return (2);
		else if (hit_list->obj->csg_operator == 1)
			return(binary_object_intersection(hit_list, inter, cam));
		else if (hit_list->obj->csg_operator == 2)
			return(binary_object_difference(hit_list, inter, cam));
		else if (hit_list->obj->csg_operator == 3)
			return(binary_object_union(hit_list, inter, cam));
		return (2);
}

