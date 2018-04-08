/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 05:21:41 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 05:22:32 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_word(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (count == 0 && *s != c)
		{
			count = 1;
			i++;
		}
		else if (count == 1 && *s == c)
			count = 0;
		s++;
	}
	return (i);
}

static int		ft_current_word_len(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		index;
	int		nb_word;

	if (s)
	{
		index = 0;
		nb_word = ft_nb_word(s, c);
		if (!(tab = (char**)malloc(sizeof(char*) * (nb_word + 1))))
			return (NULL);
		while (nb_word--)
		{
			while (*s == c && *s != '\0')
				s++;
			tab[index] = ft_strsub(s, 0, ft_current_word_len(s, c));
			if (tab[index] == NULL)
				return (NULL);
			s = s + ft_current_word_len(s, c);
			index++;
		}
		tab[index] = NULL;
		return (tab);
	}
	return (NULL);
}
