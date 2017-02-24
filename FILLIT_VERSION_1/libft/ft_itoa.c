/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:09:10 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:09:14 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strnbr(int n, int i, int j, char **str)
{
	if (n == -2147483648)
		*str = "-2147483648";
	else if (n < 0)
	{
		*str[0] = '-';
		ft_strnbr(-n, 0, j, str);
	}
	else if (n >= 10)
	{
		ft_strnbr(n / 10, ++i, j, str);
		ft_strnbr(n % 10, --i, j, str);
	}
	else if (n < 10)
		str[0][j - i] = n + 48;
}

char			*ft_itoa(int n)
{
	char	*str;
	int		j;
	int		i;
	int		nb;

	i = 0;
	j = 0;
	nb = n;
	str = malloc(sizeof(*str) * (12));
	str[0] = '0';
	if (n == 0)
		return (str);
	while (nb != 0)
	{
		nb = nb / 10;
		j++;
	}
	if (n < 0)
		j++;
	ft_strnbr(n, i, j - 1, &str);
	if (n != -2147483648)
		str[j] = 0;
	return (str);
}
