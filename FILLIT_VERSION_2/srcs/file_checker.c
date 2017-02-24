/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 03:27:35 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:13:54 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		valid_char(char *buff, int ret)
{
	int i;
	int bloc;

	i = -1;
	bloc = 0;
	while (++i < 20)
	{
		if (i % 5 < 4)
		{
			if (buff[i] != '.' && buff[i] != '#')
				return (1);
			if (buff[i] == '#' && ++bloc > 4)
				return (2);
		}
		else if ((i % 5 == 4) && buff[i] != '\n')
			return (3);
	}
	if (ret == 21 && buff[20] != '\n')
		return (4);
	return (0);
}

int		connection(char *buff)
{
	int i;
	int counter;

	i = -1;
	counter = 0;
	while (++i < 20)
	{
		if (buff[i] == '#')
		{
			if (i - 1 >= 0 && buff[i - 1] == '#')
				counter++;
			if (i + 1 < 20 && buff[i + 1] == '#')
				counter++;
			if (i - 5 >= 0 && buff[i - 5] == '#')
				counter++;
			if (i + 5 < 20 && buff[i + 5] == '#')
				counter++;
		}
	}
	return (counter == 6 || counter == 8);
}

void	err_exit(void)
{
	ft_putstr("error\n");
	exit(1);
}
