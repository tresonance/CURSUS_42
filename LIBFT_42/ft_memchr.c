/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 02:34:53 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/22 21:00:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	c1;

	i = 0;
	str = NULL;
	str = (unsigned char*)s;
	c1 = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == c1)
			return ((void*)(str + i));
		i++;
	}
	return (NULL);
}
