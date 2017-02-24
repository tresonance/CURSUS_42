/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:44:24 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/18 22:44:30 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int a;
	int *ret;
	int b;

	b = 0;
	a = max;
	a -= min;
	if (min < max)
	{
		if ((ret = (int*)malloc(sizeof(int) * a)) == NULL)
			return (NULL);
		while (min < max)
		{
			ret[b] = min;
			b = b + 1;
			min = min + 1;
		}
		return (ret);
	}
	return (0);
}
