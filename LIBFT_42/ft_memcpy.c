/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:34:33 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 08:39:13 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n > 0)
	{
		n--;
		((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
	}
	return (dest);
}
