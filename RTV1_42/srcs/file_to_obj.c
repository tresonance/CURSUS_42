/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 03:39:26 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/10 23:22:56 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

static int	get_obj1(t_obj **new, char ***tab, int *i)
{
	(*new)->name = ft_strdup((*tab)[*i]);
	*i += 1;
	if (0 != ft_strcmp("	{", (*tab)[*i]))
		return (0);
	*i += 1;
	if (0 == get_col(*new, *tab, i))
		return (0);
	if (0 == get_pos(*new, *tab, i))
		return (0);
	return (1);
}

int			get_obj(t_list **obj, char **tab, int *i)
{
	t_obj	*new;
	t_list	*lstnew;

	if (NULL == (new = (t_obj *)malloc(sizeof(t_obj))))
		return (0);
	if (0 == get_obj1(&new, &tab, i))
		return (0);
	if (0 != ft_strcmp("	light", new->name))
	{
		if (ft_strcmp("	plane", new->name) && 0 == get_size(new, tab, i))
			return (0);
		if (ft_strcmp("	sphere", new->name) && 0 == get_rot(new, tab, i))
			return (0);
		if (0 == get_light_info(new, tab, i))
			return (0);
	}
	if (0 != ft_strcmp("	}", tab[*(i++)]))
		return (0);
	new->current = 0;
	if (NULL == (lstnew = ft_lstnew(NULL, 0)))
		return (0);
	lstnew->content = new;
	lst_add_back(obj, lstnew);
	return (1);
}

int			parser_obj(t_list **obj, char **tab, int i)
{
	if (NULL == tab[i])
		return (0);
	while (0 == ft_strcmp("", tab[i]))
		i += 1;
	if (NULL == tab[i])
		return (0);
	if (0 != ft_strcmp("content", tab[i++]))
		return (0);
	if (0 != ft_strcmp("{", tab[i++]))
		return (0);
	while (tab[i] != NULL)
	{
		if (0 == ft_strcmp("	light", tab[i]) ||
			0 == ft_strcmp("	plane", tab[i]) ||
			0 == ft_strcmp("	cylinder", tab[i]) ||
			0 == ft_strcmp("	cone", tab[i]) ||
			0 == ft_strcmp("	sphere", tab[i]))
		{
			if (0 == get_obj(obj, tab, &i))
				return (0);
		}
		else
			i += 1;
	}
	return (1);
}
