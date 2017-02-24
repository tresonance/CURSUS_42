/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:22:53 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:22:54 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*s2 == 0)
		return ((char *)s1);
	while (s1[i] && s1[i] != s2[j])
		i++;
	if (s1[i] == 0)
		return (NULL);
	else if (s1[i] == s2[j])
	{
		while (s2[j] == s1[i + j] && s2[j])
			j++;
		if (s2[j] == 0)
			return ((char *)(s1 + i));
		else
		{
			i++;
			return (ft_strstr(s1 + i, s2));
		}
	}
	return (NULL);
}
