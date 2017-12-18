/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:13:02 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/23 20:12:03 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * ft_count_digit(n) + 1);
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	else if (n == 0)
		return (ft_strcpy(str, "0"));
	return (ft_strrev(ft_strnbr(str, n)));
}
