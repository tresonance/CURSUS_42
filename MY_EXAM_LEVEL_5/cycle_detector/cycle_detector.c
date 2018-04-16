#include "list.h"

int					cycle_detector(const t_list *list)
{
	t_list			*slow_pointer;
	t_list			*fast_pointer;

	if(list == NULL)
		return (0);
	slow_pointer = (t_list*)list;
	fast_pointer = (t_list*)list;

	while(slow_pointer && fast_pointer && fast_pointer->next)
	{
		slow_pointer = slow_pointer->next;
		fast_pointer = fast_pointer->next->next;
		if(slow_pointer == fast_pointer)
			return (1);
	}
	return (0);
}
