/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:11:14 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:11:15 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list **alstm, t_list *new)
{
	t_list *tmp;

	if (*alstm == NULL)
	{
		return (new);
	}
	else
	{
		tmp = *alstm;
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	tmp->next = new;
	return (*alstm);
}
