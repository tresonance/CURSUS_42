/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 00:22:46 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/27 05:55:29 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strclen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t			i;
	unsigned int	j;
	int				k;
	char			**tab;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tab = (char**)malloc(sizeof(char*) * ft_count_words(s, c) + 1);
	if (!tab)
		return (NULL);
	j = 0;
	while (k < ft_count_words(s, c))
	{
		while (s[j] == c)
			j++;
		tab[k] = ft_strsub(s, j, ft_strclen(&s[j], c));
		j += ft_strclen(&s[j], c);
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
