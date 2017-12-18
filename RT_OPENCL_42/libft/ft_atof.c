/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 01:04:18 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 15:07:05 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
			|| c == '\f' || c == '\v');
}

static int			nb_size(char *nb)
{
	int				i;

	i = 0;
	while (nb[i] != '\0' && 1 == ft_isdigit(nb[i]))
		i += 1;
	return (i);
}

static float		get_integer_part(char *nb, int *i)
{
	int				exp;
	int				size;
	float			result;

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

static float		get_float_part(int neg, float result, char *nb, int *i)
{
	int				exp;

	exp = 10;
	while (nb[*i] != '\0' && 1 == ft_isdigit(nb[*i]))
	{
		result += (float)(nb[*i] - '0') / exp;
		exp *= 10;
		*i += 1;
	}
	if (neg == 1)
		result = -result;
	return (result);
}

float				ft_atof(char *nb)
{
	int				neg;
	float			result;
	int				i;

	i = 0;
	while (1 == ft_iswhitespace(nb[i]))
		i++;
	if (nb[i] == '-')
	{
		i += 1;
		neg = 1;
	}
	else
		neg = 0;
	result = get_integer_part(nb, &i);
	result = get_float_part(neg, result, nb, &i);
	return (result);
}
