/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 23:15:28 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/10 23:38:24 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn.h"

int			num_word(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (count == 0  && *s != c)
		{
			count = 1;
			i++;
		}
		else if (count && *s == c)
			count = 0;
		s++;
	}
	return (i);
}

int			curr_len(char const  *str, char c)
{
	int len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

char			*cheat_strcpy(char *dest, char const *src, char c)
{
	int i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			**ft_strsplit(char const *str, char c)
{
	char		**tab;
	int len;
	int i;
	int cur_len;

	if (*str)
	{
		len = num_word(str, ' ');
		if (!(tab = (char**)malloc((len + 1) * sizeof(char*))))
			return (NULL);
		i = -1;
		while (len--)
		{
			while (*str && *str == c)
				str++;
			cur_len = curr_len(str, ' ');
			if (!(tab[++i] = (char*)malloc((cur_len + 1) * sizeof(char))))
				return (NULL);
			cheat_strcpy(tab[i], str, ' ');
			str += cur_len;
		}
		tab[i + 1] = NULL;
		return (tab);
	}
	return (NULL);
}
