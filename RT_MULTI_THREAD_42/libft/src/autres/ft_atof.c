/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 02:24:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/23 06:15:11 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			nb_size(char *nb)
{
	int				i;

	i = 0;
	while (nb[i] != '\0' && 1 == ft_isdigit(nb[i]))
		i += 1;
	return (i);
}

static double		get_integer_part(char *nb, int *i)
{
	int				exp;
	int				size;
	double			result;

	result = 0;
	exp = 1;
	size = nb_size(&nb[*i]);
	while (1 < size)
	{
		exp *= 10;
		size -= 1;
	}
	while (nb[*i] != '\0' && 1 == ft_isdigit(nb[*i]))
	{
		result += (nb[*i] - '0') * exp;
		exp /= 10;
		*i += 1;
	}
	if (nb[*i] == '.')
		*i += 1;
	return (result);
}

static double		get_float_part(int neg, double result, char *nb, int *i)
{
	int				exp;

	exp = 10;
	while (nb[*i] != '\0' && 1 == ft_isdigit(nb[*i]))
	{
		result += (double)(nb[*i] - '0') / exp;
		exp *= 10;
		*i += 1;
	}
	if (neg == 1)
		result = -result;
	return (result);
}

double				ft_atof(char *nb, int *i)
{
	int				neg;
	double			result;

	while (1 == ft_iswhitespace(nb[*i]))
		*i += 1;
	if (nb[*i] == '-')
	{
		*i += 1;
		neg = 1;
	}
	else
		neg = 0;
	result = get_integer_part(nb, i);
	result = get_float_part(neg, result, nb, i);
	return (result);
}
