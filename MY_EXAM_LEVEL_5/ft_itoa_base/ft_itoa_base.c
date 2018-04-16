/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 22:54:09 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/10 23:07:46 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int				lena(long nbr, long base)
{
	int			len;

	len = 1;
	while (nbr/base)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

char		*ft_itoa_base(int value, int base)
{
	long	n;
	int		negatif;
	char	baz[] = "0123456789ABCDEF";
	int		len;
	char	*tab;

	negatif = 0;
	n = value;
	if (n < 0)
	{
		if (base == 10)
			negatif = 1;
		n *= -1;
	}
	len = lena(n, base);
	if (!(tab = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	tab += len;
	*tab = '\0';
	while ((*--tab = baz[n % base]) && (n /= base))
		;
	if (negatif)
		*--tab = '-';
	return (tab);
}

