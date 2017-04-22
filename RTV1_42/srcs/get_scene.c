/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 08:04:26 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:14:45 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

static int	file_to_list(char *file, t_list **list, size_t *size)
{
	int		fd;
	char	*line;
	t_list	*new;

	if (0 > (fd = open(file, O_RDONLY)))
		return (0);
	while (0 < get_next_line(fd, &line))
	{
		*size += 1;
		if (NULL == (new = ft_lstnew(NULL, 0)))
		{
			close(fd);
			return (0);
		}
		new->content = (void *)line;
		lst_add_back(list, new);
	}
	close(fd);
	return (1);
}

static char	**list_to_tab(t_list *list, size_t size)
{
	char	**tab;
	t_list	*tmp;
	size_t	i;

	i = 0;
	tmp = list;
	if (NULL == (tab = (char **)malloc(sizeof(char *) * (size + 2))))
		return (NULL);
	while (i < size)
	{
		tab[i] = (char *)tmp->content;
		tmp = tmp->next;
		i += 1;
	}
	if (NULL == (tab[i] = (char *)malloc(sizeof(char))))
		return (NULL);
	tab[i][0] = '\0';
	tab[i + 1] = NULL;
	return (tab);
}

int			parser(t_list **obj, t_cam *cam, char **tab)
{
	t_list	*tmp;
	int		i;

	if (0 == parser_cam(cam, tab))
		return (0);
	if (0 == parser_obj(obj, tab, 5))
		return (0);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i += 1;
	}
	free(tab[i]);
	free(tab);
	return (1);
}

int			get_scene(t_list **obj, t_cam *cam, char *file)
{
	t_list	*list;
	char	**tab;
	size_t	size;
	t_list	*tmp;

	list = NULL;
	size = 0;
	if (0 == file_to_list(file, &list, &size))
		return (0);
	if (NULL == (tab = list_to_tab(list, size)))
		return (0);
	while (list)
	{
		tmp = list;
		list = tmp->next;
		free(tmp);
	}
	if (0 == parser(obj, cam, tab))
		return (0);
	return (1);
}
