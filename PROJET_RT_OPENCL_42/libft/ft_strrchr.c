/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 07:51:59 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/18 21:52:17 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int j;
	int k;

	i = ft_strlen(s);
	k = 0;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			j = ft_strlen(s) - (k);
			return ((char*)s + j);
		}
		i--;
		k++;
	}
	return (NULL);
}
