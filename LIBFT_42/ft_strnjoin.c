/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 07:10:58 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 07:11:16 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(const char *s1, const char *s2, size_t n)
{
	char	*s3;

	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (NULL);
	}
	if (!s1 || !*s1)
		return (ft_strndup(s2, n));
	s3 = ft_strnew(ft_strlen(s1) + n);
	if (s3 == NULL)
		return (NULL);
	s3 = ft_strcpy(s3, s1);
	s3 = ft_strncat(s3, s2, n);
	return (s3);
}
