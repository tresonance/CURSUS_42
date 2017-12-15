/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 22:55:30 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/30 02:03:28 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lstmap;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	lstmap = (t_list*)malloc(sizeof(lst));
	if (!lstmap)
		return (NULL);
	lstmap = f(lst);
	tmp = lstmap;
	while (lst->next)
	{
		tmp->next = f(lst->next);
		tmp = lstmap->next;
		lst = lst->next;
	}
	return (lstmap);
}
