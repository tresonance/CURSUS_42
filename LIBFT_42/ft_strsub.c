/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 00:11:18 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/20 00:11:27 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dest;

	dest = ft_memalloc(1);
	if (s && len > 0)
	{
		dest = (char*)malloc(sizeof(char) * (len + 1));
		if (dest)
		{
			i = 0;
			while (len--)
				dest[i++] = s[start++];
			dest[i] = '\0';
		}
	}
	return (dest);
}
