/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:21:25 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:21:26 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*s2;
	int		i;
	int		nb;

	i = 0;
	nb = ft_strlen(s1);
	if (nb > n)
		nb = n;
	if (nb == 0)
	{
		s2 = malloc(sizeof(*s1));
		*s2 = 0;
		return (s2);
	}
	s2 = malloc(sizeof(*s1) * (nb + 1));
	while (i < nb)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
