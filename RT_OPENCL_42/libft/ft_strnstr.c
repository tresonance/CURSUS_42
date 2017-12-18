/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 07:57:31 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/20 09:29:45 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	s;

	i = 0;
	while (big[i] && len > 0)
	{
		if (len < ft_strlen(little))
			return (NULL);
		k = 0;
		s = i;
		while (big[s] == little[k] && little[k] && big[s])
		{
			k++;
			s++;
		}
		if (little[k] == '\0')
			return ((char *)big + i);
		len--;
		i++;
	}
	return (NULL);
}
