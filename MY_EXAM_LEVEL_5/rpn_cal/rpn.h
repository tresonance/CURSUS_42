/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 23:11:32 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/11 00:07:03 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
# define RPN_H

#include <stdlib.h>
# include <stdio.h>

#define MAX 400

typedef struct s_tack
{
	long	data[MAX];
	long		top;
}				t_stack;

char			**ft_strsplit(char const *s, char c);
t_stack			*get_stack(void);
int				is_full(t_stack *s);
int				is_empty(t_stack *s);
void			push(t_stack *s, long val);
long			pup(t_stack *s);
#endif
