/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 23:13:41 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/11 00:42:37 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn.h"

t_stack			*get_stack(void)
{
	t_stack *s;

	if (!(s = (t_stack*)malloc(sizeof(t_stack))))
		return (NULL);
	s->top = -1;
	return (s);
}

int			is_full(t_stack *s)
{
	if (s->top == MAX)
		return (1);
	return (0);
}

int			is_empty(t_stack *s)
{
	if (s->top == -1)
		return (1);
	return (0);
}

void		push(t_stack *s, long  val)
{
	if (!is_full(s))
	{
		s->top = s->top + 1;
		s->data[s->top] = val;
	}
}

long		pup(t_stack *s)
{
	long data;

	if (!is_empty(s))
	{
		data = s->data[s->top];
		s->top = s->top - 1;
		return (data);
	}
	return (2147483648);
}
