/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:19:31 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:19:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		nb;

	i = 0;
	nb = ft_strlen(s1);
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
