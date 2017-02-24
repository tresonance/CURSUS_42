/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:11:31 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:11:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while ((unsigned char)c != *(unsigned char *)src && n)
	{
		n--;
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	if ((n == 0 && (unsigned char)c != *(unsigned char *)src))
		return (NULL);
	else
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		return (dst);
	}
}
