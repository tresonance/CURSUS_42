/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump_co.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 23:39:26 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:42:21 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_bump_co1(char *str, char **str2, t_text *bump, int *j)
{
	int			i;

	if (ft_strcmp("bump_yoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			bump[*j].yoffset = ft_atof(str2[i]);
	}
	if (ft_strcmp("bump_startoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			bump[*j].startoffset.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("bump_end", str) == 0)
		*j += 1;
}

void			parse_bump_co2(char *str, char **str2, t_text *bump, int j)
{
	int			i;

	if (ft_strcmp("bump_id", str) == 0)
	{
		i = -1;
		while (str2[++i])
			bump[j].id = ft_atof(str2[i]);
	}
	if (ft_strcmp("bump_pos", str) == 0)
	{
		i = -1;
		while (str2[++i])
			bump[j].pos = ft_atof(str2[i]);
	}
	if (ft_strcmp("bump_xoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			bump[j].xoffset = ft_atof(str2[i]);
	}
}

void			parse_bump_co(char *str, char **str2, t_text *bump, int *i)
{
	parse_bump_co1(str, str2, bump, i);
	parse_bump_co2(str, str2, bump, *i);
}

void			parse_bump(char *str, t_scene *scene)
{
	int			fd;
	int			i;
	char		*line;
	char		**tab;
	char		**tab2;

	if (-1 == (fd = open(str, O_RDONLY)))
		return ;
	i = 1;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp("", line) != 0)
		{
			tab = ft_strsplit(line, '=');
			tab2 = ft_strsplit(tab[1], ',');
			parse_bump_co(tab[0], tab2, scene->bump, &i);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}
