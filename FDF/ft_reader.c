/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 07:08:11 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 23:48:11 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				is_valid_char(char *line)
{
	int			i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '-')
			return (0);
	}
	return (1);
}

void			line_col(char *file, t_env *e)
{
	int			fd;
	char		*line;
	char		**tab;
	int			i;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_err_exit("Failed to open file");
	while (get_next_line(fd, &line) > 0)
	{
		if (e->col == 0)
		{
			i = -1;
			tab = ft_strsplit(line, ' ');
			while (tab[++i])
				;
			e->col = i;
			ft_destroy_tab(tab);
		}
		ft_strdel(&line);
		e->line++;
	}
	close(fd) == -1 ? ft_err_exit("Failed to close") : 0;
}

int				get_col(char **tab)
{
	int			i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

void			ft_add_line_data(t_line **line, char *read_line, int num_line)
{
	int			i;
	char		**tab;

	i = -1;
	tab = ft_strsplit(read_line, ' ');
	while (tab[++i])
	{
		(*line)->points[i]->x = i;
		(*line)->points[i]->y = num_line;
		(*line)->points[i]->z = ft_atoi(tab[i]);
		(*line)->points[i]->w = 1.0;
		(*line)->points[i]->color = (ft_atoi(tab[i]) > 0) ? ft_atoi(tab[i]) :
			-1 * ft_atoi(tab[i]);
	}
}

void			ft_reader(t_env *e, char *file)
{
	int			fd;
	char		*line;
	char		**tab;
	int			num_line;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_err_exit("Failed to open file");
	line_col(file, e);
	get_map(&(e->map), e);
	num_line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!is_valid_char(line))
			ft_err_exit("Bad character");
		tab = ft_strsplit(line, ' ');
		if (e->col != get_col(tab))
			ft_err_exit("Wrong column number");
		ft_add_line_data(&((e->map)->lines[num_line]), line, num_line);
		num_line++;
		ft_destroy_tab(tab);
		ft_strdel(&line);
	}
	if (e->col == 0 || e->line == 0)
		ft_err_exit("Empty file");
	close(fd) == -1 ? ft_err_exit("Failed to close file") : 0;
}
