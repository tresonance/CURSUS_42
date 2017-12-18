/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:55:00 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 04:57:04 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		lst_add_back(t_list **lst, t_list *new)
{
        t_list  *tmp;

        if (*lst == NULL)
                *lst = new;
        else
        {
                tmp = *lst;
                while (tmp->next)
                        tmp = tmp->next;
                tmp->next = new;
        }
}

static int	file_to_list(char *file, t_list **list, size_t *size)
{
	int		fd;
	char	*line;
	t_list	*new;
	int		is_empty_file;

	if (0 > (fd = open(file, O_RDONLY)))
		return (0);
	is_empty_file = 0;
	while (0 < get_next_line(fd, &line))
	{
		*size += 1;
		if (NULL == (new = ft_lstnew(NULL, 0)))
		{
			close(fd);
			return (0);
		}
		new->content = (void *)line;
		new->next = NULL;
		lst_add_back(list, new);
		is_empty_file++;
	}
	if (!is_empty_file)
		return (0);
	close(fd) == -1 ? err_exit("Unable to close file") : 0;
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

int			parser(t_obj **obj, t_cam *cam, char **tab)
{
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
	if (tab[i])
		free(tab[i]);
	if (tab)
		free(tab);
	return (1);
}

int			get_scene(t_obj **obj, t_cam **cam, char *file)
{
	t_list	*list;
	char	**tab;
	size_t	size;
	t_list	*tmp;

	list = NULL;
	size = 0;
	if (0 == file_to_list(file, &list, &size))
	{
		err_exit("ERROR : EXPECTED SCENE FILE");
		return (0);
	}
	if (NULL == (tab = list_to_tab(list, size)))
		return (0);
	while (list)
	{
		tmp = list;
		list = tmp->next;
		free(tmp);
	}
	list = NULL;
	if (0 == parser(obj, *cam, tab))
		return (0);
	return (1);
}

int			scene(char *file, t_cam **cam, t_obj **obj, t_light **light_point, t_light_obj **light_obj)
{
	t_obj *del;
	t_obj *tmp;
	int index;
	
	get_scene(obj, cam, file);
	while (*obj && ft_strcmp((*obj)->name, "\tlight") == 0)
	{
			add_light_source_to_scene(light_point, *obj);
			del = (*obj);
			(*obj) = del->next;
			free(del->name);
			free(del);
	}
	tmp = *obj;
	index = 0;
	while (tmp)
	{	
		tmp->obj_index = index++;
		if (tmp->is_light_obj)
			add_light_obj_to_scene(light_obj, tmp);
		tmp = tmp->next;
	}
	//ft_remove_if(obj);
	return (1);
}
