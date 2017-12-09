/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:49:01 by fsidler           #+#    #+#             */
/*   Updated: 2017/05/06 13:16:41 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_str_join_free(char *s1, char *s2, char type)
{
	if (type == 'L')
		ft_strdel(&s1);
	else if (type == 'R')
		ft_strdel(&s2);
	else if (type == 'B')
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
}

char		*ft_strjoin_free(char *s1, char *s2, char type)
{
	char	*n;
	int		i[2];

	i[0] = 0;
	while (s1[i[0]])
		i[0]++;
	i[1] = 0;
	while (s2[i[1]])
		i[1]++;
	n = (char *)malloc(sizeof(char) * (i[0] + i[1] + 1));
	i[0] = 0;
	while (s1[i[0]])
	{
		n[i[0]] = s1[i[0]];
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		n[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	ft_str_join_free(s1, s2, type);
	n[i[0] + i[1]] = '\0';
	return (n);
}
