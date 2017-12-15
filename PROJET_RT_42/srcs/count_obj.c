/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 02:42:57 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:36:50 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		count_obj(char *str, t_scene *scene)
{
	int		fd;
	char	*line;

	if (-1 == (fd = open(str, O_RDONLY)))
		return ;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "prim_end=end") == 0)
			scene->info->nb_prim++;
		if (ft_strcmp(line, "light_end=end") == 0)
			scene->info->nb_light++;
		if (ft_strcmp(line, "text_end=end") == 0)
			scene->info->nb_text++;
		if (ft_strcmp(line, "bump_end=end") == 0)
			scene->info->nb_bump++;
		if (ft_strcmp(line, "mat_end=end") == 0)
			scene->info->nb_mat++;
		free(line);
	}
	close(fd);
}
