/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:23:35 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:23:42 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fill(char *str, char (*buf)[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		str[i] = (*buf)[i];
		i++;
	}
	str[i] = '\0';
	return (i);
}

static void	ft_clear(char (*buf)[], int start, int end)
{
	int	i;

	i = 0;
	while (i <= start)
		(*buf)[i++] = 0;
	i = 0;
	while (start + i < end)
	{
		(*buf)[i] = (*buf)[start + i + 1];
		(*buf)[start + i + 1] = 0;
		i++;
	}
}

static char	*ft_line(char (*buf)[], int i)
{
	char *str;

	if (!(str = malloc(sizeof(str) * (i + 1))))
		return (NULL);
	ft_fill(str, buf, i);
	ft_clear(buf, i, ft_strlen(*buf));
	return (str);
}

static int	ft_readall(char **line, char (*buf)[], int i, const int fd)
{
	int nb;
	int cmpt;
	int	ret;

	nb = 0;
	cmpt = i;
	while ((ret = read(fd, &((*buf)[i]), BUFF_SIZE)) > 0)
	{
		nb = cmpt;
		cmpt += ret;
		if (nb >= cmpt)
		{
			*line = ft_line(buf, i);
			return (0);
		}
		i = 0;
		while ((*buf)[i] != '\0' && (*buf)[i] != '\n')
			i++;
		if ((*buf)[i] == '\n')
		{
			*line = ft_line(buf, i);
			return (1);
		}
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE];
	int			i;
	int			cmpt;
	int			nb;

	i = 0;
	nb = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		*line = ft_line(&buf, i);
		return (1);
	}
	cmpt = i;
	if (ft_readall(line, &buf, i, fd) == 0)
		return (0);
	return (1);
}
