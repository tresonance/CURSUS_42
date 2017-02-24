/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:22:27 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:22:29 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*s2 == 0)
		return ((char *)(s1));
	while (s1[i] && (unsigned char)s1[i] != (unsigned char)s2[j] && i < n)
		i++;
	if (s1[i] == 0 || i > n)
		return (NULL);
	else if ((unsigned char)s1[i] == (unsigned char)s2[j])
	{
		while ((unsigned char)s2[j] == (unsigned char)s1[i + j]
				&& s2[j] && i + j < n)
			j++;
		if (s2[j] == 0)
			return ((char *)(s1 + i));
		else if (i++ + j >= n)
			return (NULL);
		else
			return (ft_strnstr(s1 + i, s2, n - i));
	}
	return (NULL);
}
