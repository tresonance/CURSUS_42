/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 02:51:04 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 02:51:09 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int	main(int ac, char **av)
{
	t_fillit fillit;

	if (ac < 2)
		ft_putstr("usage : FILE MISSING\n");
	else if (ac > 2)
		ft_putstr("usage : TOO MANY FILES\n");
	else
	{
		if (!(map_check(av[1], &fillit)))
		{
			ft_putstr("error\n");
			return (0);
		}
		ft_resolve(&fillit);
	}
	return (0);
}
