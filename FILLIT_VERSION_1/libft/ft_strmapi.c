/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:20:52 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:20:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	int				nb;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	nb = 0;
	while (s[nb])
		nb++;
	str = malloc(sizeof(*str) * (nb + 1));
	while (s[i])
	{
		*str = (*f)(i, s[i]);
		str++;
		i++;
	}
	*str = 0;
	return (str - nb);
}
