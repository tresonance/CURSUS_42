/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 02:49:57 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 02:50:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void		ft_destroy_map(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char		**ft_creat_map(t_fillit *fillit)
{
	char	**tet;
	int		i;
	int		j;

	if (!(tet = (char**)malloc(sizeof(char*) * fillit->size_map_min + 1)))
		return (NULL);
	i = -1;
	while (++i < fillit->size_map_min)
	{
		tet[i] = ft_strnew(fillit->size_map_min + 1);
		j = -1;
		while (++j < fillit->size_map_min)
			tet[i][j] = '.';
		tet[i][fillit->size_map_min] = '\n';
	}
	tet[fillit->size_map_min] = 0;
	return (tet);
}

int			is_fillable(t_fillit *fillit, char *tetris, int x, int y)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = x;
	while (tetris[++i])
	{
		if (ft_isalpha(fillit->map[y][x]) && ft_isalpha(tetris[i]))
			return (0);
		if (tetris[i] != '\n')
			x++;
		if (x > fillit->size_map_min)
			return (0);
		if (tetris[i] == '\n')
		{
			y++;
			x = tmp;
			if (y > fillit->size_map_min - 1)
				return (0);
		}
	}
	return (1);
}
