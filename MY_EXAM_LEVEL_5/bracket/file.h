/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 08:35:15 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/04 08:49:52 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H

# define FILE_H
# include <unistd.h>
# define MAX 400

typedef struct s_tack
{
	char		data[MAX];
	int			top;
}				t_stack;

# endif
