/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:12:23 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:12:24 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)dst;
	if (dst < src)
	{
		while (len--)
			*str++ = *(unsigned char *)src++;
	}
	else if (dst == src)
		return (dst);
	else
	{
		while (len--)
			*(str + len) = *(unsigned char*)(src + len);
	}
	return (dst);
}
