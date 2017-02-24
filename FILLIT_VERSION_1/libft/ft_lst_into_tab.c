/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_into_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:09:33 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:09:36 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_lst_into_tab(t_list *lst)
{
	t_list	*tmp;
	void	**tab;
	int		i;

	tab = malloc(sizeof(tab) * (ft_lst_size(lst) + 1));
	tmp = lst;
	i = 0;
	while (tmp)
	{
		tab[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}
