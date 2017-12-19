/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:28:54 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 08:38:46 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*new_str;
	unsigned int	i;

	i = 0;
	new_str = (unsigned char*)str;
	while (i < n)
	{
		new_str[i] = (char)c;
		i++;
	}
	return (str);
}
