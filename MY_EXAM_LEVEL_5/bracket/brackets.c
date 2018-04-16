/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 08:34:45 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/11 02:22:28 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int			is_pair(char c, char d)
{
	if (c == '(' && d == ')')
		return (1);
	else if (c == '[' && d == ']')
		return (1);
	else if (c == '{' && d == '}')
		return(1);
	return (0);
}

int		is_open(int c)
{
	return (c == '{' || c == '[' || c == '(');
}

int		is_close(int c)
{
	return (c == '}' || c == ']' || c == ')');
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

void		push(t_stack *s, char c)
{
	if (!is_full(s))
	{
		s->top = s->top + 1;
		s->data[s->top] = c;
	}
}

char		pup(t_stack *s)
{
	char data;
	if (!is_empty(s))
	{
		data = s->data[s->top];
		s->top = s->top - 1;
		return (data);
	}
	return ('\0');
}

int		bracket(char *str)
{
	int i;
	t_stack s;

	i = -1;
	s.top = -1;
	while (str[++i])
	{
		if (is_open(str[i]))
			push(&s, str[i]);
		else if (is_close(str[i]))
		{
			if (s.top == -1)
				return (0);
			else if (!is_pair(pup(&s), str[i]))
				return (0);
		}
	}
	if (s.top == -1)
		return (1);
	else
		return (0);
}


int		main(int argc , char **argv)
{
	int res;
	int i;

	if (argc >= 2)
	{
		i = 1;
		while (i < argc)
		{
			res = bracket(argv[i]);
			if (res)
				write (1, "OK", 2);
			else
				write (1, "Error", 5);
			if (i < argc - 1)
				write (1, "\n", 1);
			i++;
		}
	}
	write (1 , "\n", 1);
	return (0);
}
