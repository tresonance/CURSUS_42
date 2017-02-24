/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:10:56 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:10:58 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstadd_end(t_list **begin_list, t_list *end_elt)
{
	t_list		*i;

	if (*begin_list)
	{
		i = *begin_list;
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = end_elt;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;

	new_list = (*f)(lst);
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_end(&new_list, (*f)(lst));
		lst = lst->next;
	}
	return (new_list);
}
