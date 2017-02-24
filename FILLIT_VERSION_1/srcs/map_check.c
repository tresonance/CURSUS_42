/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 02:51:19 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 02:51:23 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

static int	valid_map(char *map, int a, int nbofsharp, int count)
{
	while (map[++a])
	{
		if (map[a] == '#')
			nbofsharp++;
		if ((++count % 5) == 0 && map[a] != '\n')
			return (0);
		if (map[a] != '#' && map[a] != '.' && map[a] != '\n')
			return (0);
		if (count == 21)
		{
			if (nbofsharp != 4 || map[a] != '\n')
				return (0);
			nbofsharp = 0;
			count = 0;
		}
	}
	if (count != 20 || nbofsharp != 4)
		return (0);
	return (1);
}

static int	check_tetris(char *map)
{
	int	touch;
	int	a;

	touch = 0;
	a = -1;
	while ((map[++a] != '\n' || map[a + 1] != '\n') && (map[a] != '\0'))
	{
		if (map[a] == '#')
		{
			touch += (map[a - 5] == '#') ? 1 : 0;
			touch += (map[a - 1] == '#') ? 1 : 0;
			touch += (map[a + 1] == '#') ? 1 : 0;
			touch += (map[a + 5] == '#') ? 1 : 0;
		}
	}
	if (touch < 6)
		return (0);
	return (1);
}

static char	*creat_tetrim(char *map, char *tetris, char letter)
{
	int		a;

	a = -1;
	if (!(tetris = (char*)malloc(sizeof(char) * 20)))
		return (NULL);
	while ((map[++a] != '\n' || map[a + 1] != '\n') && (map[a + 1] != '\0'))
	{
		if (map[a] == '#')
			tetris[a] = letter;
		else
			tetris[a] = map[a];
	}
	tetris[a] = '\0';
	return (tetris);
}

static int	creat_tetris(char *map, t_fillit *fillit)
{
	int		a;
	int		b;

	fillit->tetris_nbr = nb_tetris(map);
	b = -1;
	if (!(fillit->tetris = (char**)malloc(sizeof(char*) *
					fillit->tetris_nbr + 1)))
		return (0);
	fillit->tetris[fillit->tetris_nbr] = NULL;
	a = 0;
	while (map[++b])
	{
		if (b == 0 || (map[b] == '\n' && map[b + 1] == '\n'))
		{
			if (!(check_tetris(map + (a * 21))))
				return (0);
			if (!(fillit->tetris[a] = creat_tetrim(map + (a * 21),
					fillit->tetris[a], 'A' + a)))
				return (0);
			a++;
		}
	}
	return (1);
}

int			map_check(char *av, t_fillit *fillit)
{
	char	*map;
	int		a;

	if (!(map = map_recup(av)))
		return (0);
	if (!(valid_map(map, -1, 0, 0)))
		return (0);
	if (!(creat_tetris(map, fillit)))
		return (0);
	fillit->size_map_min = ft_sqrt(fillit->tetris_nbr * 4);
	a = -1;
	while (fillit->tetris[++a])
	{
		fillit->tetris[a] = ft_push_top(fillit->tetris[a], 'A' + a, 0, 0);
		fillit->tetris[a] = ft_push_left(fillit->tetris[a]);
		fillit->tetris[a] = ft_reduce_tetris(fillit->tetris[a], -1, 0, 0);
	}
	if (map)
	{
		free(map);
		return (1);
	}
	return (0);
}
