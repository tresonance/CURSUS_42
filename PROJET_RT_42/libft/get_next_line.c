/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:59:52 by brel-baz          #+#    #+#             */
/*   Updated: 2017/03/01 16:48:32 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*create_node(const int fd)
{
	t_line *tline;

	tline = (t_line *)malloc(sizeof(t_line));
	if (tline)
	{
		tline->fd = fd;
		tline->tmp = ft_strnew(0);
		tline->next = NULL;
	}
	return (tline);
}

t_line	*nodechr(t_line *first_tline, const int fd)
{
	t_line *tline;
	t_line *tmp;

	tline = first_tline;
	while (tline != NULL)
	{
		if (tline->fd == fd)
			return (tline);
		tmp = tline;
		tline = tline->next;
	}
	tmp->next = create_node(fd);
	return (tmp->next);
}

int		ft_get_line(char *buf, char **line, t_line *tline)
{
	char	*s1;
	char	*s2;
	char	*s3;
	int		len;

	s1 = ft_strjoin(tline->tmp, buf);
	free(tline->tmp);
	if (ft_strchr(s1, '\n') != NULL)
	{
		len = (int)(ft_strchr(s1, '\n') - s1);
		s2 = ft_strsub(s1, 0, len);
		s3 = ft_strsub(s1, len + 1, ft_strlen(s1) - len + 1);
		tline->tmp = s3;
		*line = s2;
		free(s1);
		return (1);
	}
	else
		tline->tmp = s1;
	return (0);
}

int		gnl(const int fd, char **line, t_line *tline)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	if (ft_get_line("", line, tline) == 1)
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ft_get_line(buf, line, tline) == 1)
			return (1);
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && ft_strlen(tline->tmp) > 0)
	{
		*line = ft_strdup(tline->tmp);
		ft_strclr(tline->tmp);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_line	*first_tline = NULL;
	t_line			*tline;

	if (fd < 0)
		return (-1);
	if (first_tline == NULL)
		first_tline = create_node(fd);
	tline = nodechr(first_tline, fd);
	return (gnl(fd, line, tline));
}
