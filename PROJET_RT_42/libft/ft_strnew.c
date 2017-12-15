/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 05:45:09 by brel-baz          #+#    #+#             */
/*   Updated: 2016/12/15 03:28:59 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s;

	s = (char*)malloc(sizeof(char) * size + 1);
	i = 0;
	if (!s)
		return (NULL);
	while (i <= size)
	{
		s[i] = '\0';
		i++;
	}
	s[i] = '\0';
	return (s);
}
