/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 01:08:14 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/27 00:05:30 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_node				*suitable_node(t_list **lst, int fd)
{
	t_node			*node;
	t_list			*current;

	current = *lst;
	while (current)
	{
		node = (t_node *)(current->content);
		if (node->fd == fd)
			return (node);
		current = current->next;
	}
	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->buff = ft_strnew(BUFF_SIZE);
	node->ret = BUFF_SIZE;
	node->index = BUFF_SIZE;
	node->fd = fd;
	node->new_line = 1;
	current = ft_lstnew(node, sizeof(t_node));
	ft_memdel((void **)&node);
	ft_lstadd(lst, current);
	return ((t_node *)(current->content));
}

char				*buffer_parser(t_node *node)
{
	int				i;

	i = 0;
	node->new_line = 0;
	while (node->index + i < node->ret)
	{
		if (node->buff[node->index + i] == '\n')
		{
			node->new_line = 1;
			i++;
			break ;
		}
		i++;
	}
	node->index += i;
	return (ft_strsub(node->buff, node->index - i, i - node->new_line));
}

void				delete_node(t_list **lst, int fd, char **str)
{
	t_node			*node;
	t_list			**head;
	t_list			*tmp;

	head = lst;
	while (*head)
	{
		node = (t_node *)((*head)->content);
		if (node->fd == fd)
			break ;
		*head = ((*head)->next);
	}
	if (*head)
	{
		tmp = (*head)->next;
		ft_strdel(&(node->buff));
		ft_memdel((void **)&node);
		ft_memdel((void **)head);
		*head = tmp;
	}
	ft_strdel(str);
}

int					ft_read(t_node *node, t_list **lst, char **str, char **line)
{
	if (node->index == node->ret)
	{
		node->ret = read(node->fd, node->buff, BUFF_SIZE);
		if (node->ret == -1)
		{
			delete_node(lst, node->fd, str);
			return (-1);
		}
		node->index = 0;
		if (node->ret == 0)
		{
			if (node->new_line == 0)
			{
				*line = *str;
				return (1);
			}
		}
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_node			*node;
	char			*str;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	node = suitable_node(&lst, fd);
	str = ft_strnew(0);
	while (node->ret > 0)
	{
		if ((ret = ft_read(node, &lst, &str, line)) != 0)
			return (ret);
		while (node->index < node->ret)
		{
			str = ft_strmerge(str, buffer_parser(node));
			if (node->new_line == 1)
			{
				*line = str;
				return (1);
			}
		}
	}
	delete_node(&lst, fd, &str);
	return (0);
}
