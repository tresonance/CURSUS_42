/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:20:54 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/18 22:21:00 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_factorial(int nb)
{
	int i;

	i = 1;
	if (nb == 0 || nb == 1)
	{
		return (1);
	}
	else if (nb < 0 || nb > 12)
		return (0);
	while (nb > 1)
	{
		i = nb * i;
		nb = nb - 1;
	}
	return (i);
}
