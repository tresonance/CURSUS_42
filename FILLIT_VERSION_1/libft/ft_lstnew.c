/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:11:05 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:11:08 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = malloc(sizeof(*list))) == NULL)
		return (NULL);
	if ((list->content = (void *)content) == NULL)
		list->content_size = 0;
	else
		list->content_size = content_size;
	list->next = NULL;
	return (list);
}
