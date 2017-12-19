#include "../includes/rt.h"

void		ft_remove_light_obj_from_list(t_obj **tmp, t_obj **tmp2)
{
	(*tmp2)->next = (*tmp)->next;
	free(*tmp);
	(*tmp) = (*tmp2)->next;
}

void		ft_remove_list_begin(t_obj **tmp)
{
	t_obj *tmp2;
	t_obj *tmp1;

	tmp1 = *tmp;
	while(tmp1 && tmp1->is_light_obj)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	*tmp = tmp1;
}

void		ft_remove_if(t_obj **begin_list)
{
	t_obj *tmp;
	t_obj *tmp2;

	if (*begin_list)
	{
		ft_remove_list_begin(begin_list);
		if (*begin_list)
		{
			tmp = *begin_list;
			tmp2 = tmp;
			tmp = tmp->next;
			while (tmp)
			{
				if (tmp->is_light_obj)
					ft_remove_light_obj_from_list(&tmp, &tmp2);
				else
				{
					tmp2 = tmp;
					tmp = tmp->next;
				}
			}
		}
	}
}
