/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 01:04:48 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 10:29:23 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096

typedef struct	s_node
{
	int			ret;
	int			index;
	int			new_line;
	int			fd;
	char		*buff;
}				t_node;
int				get_next_line(const int fd, char **line);
#endif
