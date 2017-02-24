/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:22:45 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:22:47 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		*ft_count_letter(char const *s, int nb, char c)
{
	int		i;
	int		j;
	int		*tab;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tab = malloc(sizeof(int) * nb);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i++] != c)
			j++;
		else
		{
			tab[k++] = j;
			j = 0;
			while (s[i] == c)
				i++;
		}
	}
	tab[k] = j;
	return (tab);
}

static int		ft_count_words(char const *str, char c)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] == c)
		i++;
	if (str[i])
		nb++;
	while (str[i])
	{
		if (str[i] != c)
			i++;
		else
		{
			while (str[i] == c)
				i++;
			if (str[i] != c && str[i] != 0)
				nb++;
		}
	}
	return (nb);
}

static char		**ft_filltab(char const *s, int *tab, char **tbstr, char c)
{
	int		nb;
	int		j;
	int		i;

	i = 0;
	j = 0;
	nb = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (j < tab[nb])
			tbstr[nb][j++] = s[i++];
		tbstr[nb][j] = 0;
		while (s[i] == c)
		{
			if ((s[i] == c) && s[i + 1] != c)
			{
				j = 0;
				nb++;
			}
			i++;
		}
	}
	return (tbstr);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		nb;
	int		*tab;
	char	**tbstr;

	i = 0;
	nb = ft_count_words(s, c);
	tab = ft_count_letter(s, nb, c);
	tbstr = malloc(sizeof(*tbstr) * (nb + 1));
	while (i < nb)
	{
		tbstr[i] = malloc(sizeof(**tbstr) * (tab[i] + 1));
		i++;
	}
	tbstr = ft_filltab(s, tab, tbstr, c);
	tbstr[nb] = NULL;
	return (tbstr);
}
