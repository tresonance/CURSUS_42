/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:11:42 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:11:45 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;

	n = n - 1;
	str = (unsigned char *)s;
	while (n-- && *(unsigned char *)str != (unsigned char)c)
		str++;
	if (*(unsigned char *)str == (unsigned char)c)
		return (str);
	else
		return (NULL);
}
