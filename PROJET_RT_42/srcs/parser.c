/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 12:54:03 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:41:51 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_cam(char *str, t_scene *scene)
{
	int			fd;
	char		*line;
	char		**tab;
	char		**tab2;

	if (-1 == (fd = open(str, O_RDONLY)))
		return ;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp("", line) != 0)
		{
			tab = ft_strsplit(line, '=');
			tab2 = ft_strsplit(tab[1], ',');
			parse_cam_co(tab[0], tab2, &scene->cam);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}

void			parse_prim(char *str, t_scene *scene)
{
	int			fd;
	int			i;
	char		*line;
	char		**tab;
	char		**tab2;

	if (-1 == (fd = open(str, O_RDONLY)))
		return ;
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp("", line) != 0)
		{
			tab = ft_strsplit(line, '=');
			tab2 = ft_strsplit(tab[1], ',');
			parse_prim_co(tab[0], tab2, scene, &i);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}

void			parse_mat(char *str, t_scene *scene)
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
			parse_mat_co(tab[0], tab2, scene, &i);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}

void			parse_text(char *str, t_scene *scene)
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
			parse_text_co(tab[0], tab2, scene, &i);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}

void			parse_light(char *str, t_scene *scene)
{
	int			fd;
	int			i;
	char		*line;
	char		**tab;
	char		**tab2;

	if (-1 == (fd = open(str, O_RDONLY)))
		return ;
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp("", line) != 0)
		{
			tab = ft_strsplit(line, '=');
			tab2 = ft_strsplit(tab[1], ',');
			parse_light_co(tab[0], tab2, scene->light, &i);
			clean_double_tab(tab, tab2);
		}
		free(line);
	}
	close(fd);
}
