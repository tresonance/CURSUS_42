/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:21:35 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:21:38 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	if (n == 0)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1)
	{
		if (s1[i] == 0)
			return (1);
		i++;
	}
	if (s1[i] == s2[i])
		return (1);
	else
		return (0);
}
