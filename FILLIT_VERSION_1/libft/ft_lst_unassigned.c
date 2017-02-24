/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_unassigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:10:05 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:10:08 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_unassigned(t_list *lst)
{
	t_list	*tmp;
	t_list	*torm;

	tmp = lst;
	while (tmp)
	{
		torm = tmp;
		tmp = tmp->next;
		torm = NULL;
	}
}
