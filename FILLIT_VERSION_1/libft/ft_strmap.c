/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:20:44 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:20:47 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		nb;

	if (s && f)
	{
		nb = 0;
		while (s[nb])
			nb++;
		str = malloc(sizeof(*str) * (nb + 1));
		while (*s)
		{
			*str = (*f)(*s++);
			str++;
		}
		*(str) = 0;
		return (str - nb);
	}
	return (NULL);
}
