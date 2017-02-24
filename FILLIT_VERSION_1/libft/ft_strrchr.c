/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:22:36 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:22:37 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *str;
	char *ptr;

	if (c == 0)
		return ((char*)s + ft_strlen(s));
	ptr = NULL;
	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			ptr = str;
		str++;
	}
	if (ptr != NULL)
		return (ptr);
	else
		return (NULL);
}
