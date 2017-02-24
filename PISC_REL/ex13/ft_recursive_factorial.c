/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:22:15 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/18 22:22:22 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_recursive_factorial(int nb)
{
	int i;

	i = 1;
	if (nb == 0 || nb == 1)
		return (1);
	else if ((nb > 0) && (nb < 13))
	{
		i = nb * (ft_recursive_factorial(nb - 1));
		return (i);
	}
	else
		return (0);
}
