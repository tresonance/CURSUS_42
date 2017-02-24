/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:22:17 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:22:20 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin_free(char *s1, char const *s2, size_t n)
{
	char	*str;
	int		k;
	int		i;
	int		j;

	k = -1;
	j = 0;
	i = 0;
	if (s1 != NULL)
		i = ft_strlen(s1);
	if (s2 != NULL)
		j = ft_strlen(s2);
	if ((size_t)j > n)
		j = n;
	if ((str = malloc(sizeof(*str) * (i + j + 1))) == 0)
		return (NULL);
	while (++k < i)
		str[k] = s1[k];
	while (k++ < (i + j))
		str[k - 1] = s2[k - i - 1];
	str[k - 1] = 0;
	free(s1);
	return (str);
}
