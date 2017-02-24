/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 04:09:31 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/05 00:14:30 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void			search_and_replace(char *buff, char a, char b)
{
	int			i;

	i = -1;
	while (buff[++i])
	{
		if (buff[i] == a)
			buff[i] = b;
	}
}

void			list_add_end(t_list **lst, char *buff, char c)
{
	t_piece		*p;
	t_piece		*p2;
	t_list		*new;
	t_list		*tmp;

	new = NULL;
	p = get_piece(buff, c);
	new = ft_lstnew(p, sizeof(t_piece));
	if (!p || !new)
		return ;
	p2 = (t_piece*)new->content;
	p2->height = p->height;
	p2->width = p->width;
	p2->c = p->c;
	p2->used = FALSE;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			reader(const int fd, t_list **lst)
{
	char		*buff;
	int			ret;
	char		c;
	char		cpy_buff[22];

	if (fd < 0)
		err_exit();
	c = 'A';
	buff = ft_strnew((BUFF_SIZE) * sizeof(char));
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ft_strcpy(cpy_buff, buff);
		if (valid_char(buff, ret) || connection(buff) == 0)
			err_exit();
		list_add_end(&(*lst), buff, c++);
	}
	if (buff[0] == '\0')
		err_exit();
	if (ft_strlen(cpy_buff) > 20 && cpy_buff[20] != '\0')
		err_exit();
}

static void		resolve(int argc, char **argv, int size)
{
	int			fd;
	t_list		*lst;
	t_map		*map;
	t_map		*mapp;
	t_point		point;

	point.x = 0;
	point.y = 0;
	lst = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		reader(fd, &lst);
		map = get_map(size);
		while (!(mapp = solver(map, &lst, point)))
		{
			free_map(&mapp);
			size++;
			map = get_map(size);
		}
		print_map(mapp);
		free_map(&mapp);
		close(fd);
	}
}

int				main(int argc, char **argv)
{
	int			size;

	size = 3;
	if (argc < 2)
		ft_putstr_fd("usage : FILE MISSING\n", 2);
	else if (argc > 2)
		ft_putstr_fd("usage : TOO MANY FILES\n", 2);
	else
		resolve(argc, argv, size);
	return (0);
}
