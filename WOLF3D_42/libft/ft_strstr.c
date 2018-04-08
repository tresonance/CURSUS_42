/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 03:31:00 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 08:54:17 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

	if (*s2 == '\0')
		return ((char*)s1);
	i = 0;
	j = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j] && (s1[i + j] == s2[j]))
			j++;
		if (s2[j] == '\0')
			return ((char*)s1 + i);
		i++;
	}
	return (NULL);
}
