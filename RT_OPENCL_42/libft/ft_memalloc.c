/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 05:22:47 by brel-baz          #+#    #+#             */
/*   Updated: 2016/12/05 16:35:27 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *str;

	if (size == 0)
		return (NULL);
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}
