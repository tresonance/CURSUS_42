/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 07:12:30 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 07:12:36 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char *dest;

	dest = ft_strnew(n);
	if (dest == NULL)
		return (NULL);
	dest = ft_strncpy(dest, src, n);
	return (dest);
}
