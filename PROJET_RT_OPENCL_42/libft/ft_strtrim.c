/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:44:10 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/27 05:33:24 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = ft_strlen(s) - 1;
	j = 0;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	if (i == j)
		return (ft_strdup(""));
	else if (i > j)
		i = i - j;
	else if (i < j)
		i = j - i;
	return (ft_strsub(s, j, i + 1));
}
