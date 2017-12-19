/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 05:51:16 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 06:00:23 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new = f(lst);
	tmp = new;
	while (lst->next)
	{
		tmp->next = f(lst->next);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (new);
}
