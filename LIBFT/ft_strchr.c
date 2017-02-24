/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 03:27:58 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 09:05:37 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	while ((str[i]) && (str[i] != c))
		i++;
	if (str[i] == c)
		return ((char*)str + i);
	else if (c == '\0')
		return ((char*)str + i + 1);
	return (NULL);
}
