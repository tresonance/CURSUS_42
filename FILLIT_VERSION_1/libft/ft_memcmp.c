/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:11:51 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:11:52 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	n = n - 1;
	while (*(unsigned char *)s1 == *(unsigned char *)s2 && n--
			&& *(unsigned char *)s1)
	{
		s1++;
		s2++;
	}
	if (*(unsigned char *)s1 == *(unsigned char *)s2)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
