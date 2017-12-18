/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 06:51:33 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/18 10:47:43 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while ((s[i]) && (s[i] != c))
		i++;
	if (s[i] == c)
		return ((char*)s + i);
	else if (c == '\0')
		return ((char*)s + i + 1);
	return (NULL);
}
