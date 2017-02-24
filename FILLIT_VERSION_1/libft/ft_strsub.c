/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:23:01 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:23:03 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= (size_t)ft_strlen(s) || start + len > (size_t)ft_strlen(s))
		return (NULL);
	if (len == 0 || s[start] == 0)
	{
		str = malloc(sizeof(*str));
		*str = 0;
		return (str);
	}
	i = 0;
	if ((str = malloc(sizeof(*str) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
