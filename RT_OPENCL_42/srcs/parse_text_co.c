/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text_co.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 02:28:35 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:10:38 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_text_co1(char *str, char **str2, t_scene *scene, int *j)
{
	int i;

	if (ft_strcmp("text_yoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->text[*j].yoffset = ft_atof(str2[i]);
	}
	if (ft_strcmp("text_startoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->text[*j].startoffset.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("text_end", str) == 0)
		*j += 1;
}

void	parse_text_co2(char *str, char **str2, t_scene *scene, int j)
{
	int i;

	if (ft_strcmp("text_id", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->text[j].id = ft_atof(str2[i]);
	}
	if (ft_strcmp("text_pos", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->text[j].pos = ft_atof(str2[i]);
	}
	if (ft_strcmp("text_xoffset", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->text[j].xoffset = ft_atof(str2[i]);
	}
}

void	parse_text_co(char *str, char **str2, t_scene *scene, int *i)
{
	parse_text_co1(str, str2, scene, i);
	parse_text_co2(str, str2, scene, *i);
}
