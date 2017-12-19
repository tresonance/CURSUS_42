/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 01:55:09 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/27 05:45:56 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *s, char c)
{
	size_t			i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while ((s[i] != c) && (s[i]))
				i++;
			words++;
		}
		while ((s[i] == c) && (s[i]))
			i++;
	}
	return (words);
}
