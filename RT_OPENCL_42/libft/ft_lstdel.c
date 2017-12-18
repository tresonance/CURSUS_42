/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 04:53:38 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/29 21:42:21 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *tmp;

	tmp = NULL;
	while (*alst != NULL)
	{
		tmp = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = tmp;
	}
}
