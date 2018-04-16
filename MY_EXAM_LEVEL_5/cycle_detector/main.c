#include "list.h"

t_list				*new_node(int data)
{
	t_list			*new;

	if(!(new = (t_list*)malloc(sizeof(t_list))))
		exit(1);
	new->data = data;
	new->next = NULL;
	return (new);
}

int		main(void) //TEST CASE
{
	t_list			*head;

	head = new_node(1);
	head->next = new_node(2);
	head->next->next = new_node(3);
	head->next->next->next = new_node(4);
	head->next->next->next->next = new_node(5);
	head->next->next->next->next->next = head->next;
	printf("CYCLE DETECTION: %s\n", cycle_detector(head) ? "TRUE" : "FALSE");
	return (0);
}
