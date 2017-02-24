/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:20:19 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:20:21 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		nb;

	i = 0;
	j = 0;
	if (size < (size_t)ft_strlen(dst) + 1)
	{
		nb = size + ft_strlen((char *)src);
		return (nb);
	}
	else
		nb = ft_strlen(dst) + ft_strlen((char *)src);
	while (dst[i] && i < size - 1)
		i++;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (nb);
}
