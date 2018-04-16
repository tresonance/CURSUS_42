/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 23:46:33 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/11 02:59:09 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn.h"

int				ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (s1[i] ==  '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

void		rpn_cal(char **tab)
{
	int i;
	t_stack *s;
	long x[3];

	i = -1;
	s = get_stack();
	if (s)
	{
		if (tab)
		{
			while (tab[++i])
			{
				if (ft_strcmp(tab[i] , "+") && ft_strcmp(tab[i] , "-") 
				&& ft_strcmp(tab[i] , "*") && ft_strcmp(tab[i] , "/") 
				&& ft_strcmp(tab[i], "%"))
				{
					push(s, atoi(tab[i]));
				}
				else if (0 == ft_strcmp(tab[i] , "+")  || 0 ==  ft_strcmp(tab[i] , "-") 
				|| 0 ==  ft_strcmp(tab[i] , "*") || 0 ==  ft_strcmp(tab[i] , "/") 
				|| 0 ==  ft_strcmp(tab[i], "%"))
				{
					if (s->top + 1  < 2)
					{
							printf("Error\n");
							return ;
					}
					if (tab[i][0] == '+')
					{
						x[0] = pup(s);
						x[1] = pup(s);
						x[2] = x[0] + x[1];
					}
					else if (tab[i][0] == '-')
					{
						x[0] = pup(s);
						x[1] = pup(s);
						x[2] = x[1] - x[0];
					}
					else if (tab[i][0] == '*')
					{
						x[0] = pup(s);
						x[1] = pup(s);
						x[2] = x[0] * x[1];
					}
					else if (tab[i][0] == '/')
					{
							x[0] = pup(s);
							x[1] = pup(s);
						if (x[0] == 0)
						{
							printf("Error\n");
							return ;
						}
						else
						{
							x[2] = x[1] / x[0];
						}
					}
					else if (tab[i][0] == '%')
					{
							x[0] = pup(s);
							x[1] = pup(s);

						if (x[0] == 0)
						{
							printf("Error\n");
							return ;
						}
						else
						{
							x[2] = x[1] % x[0];
						}
					}
					push(s, x[2]);
				}
				else
				{
					printf("Error\n");
					return ;
				}
			}
			if (s->top != 0)
			{
				printf("Error\n");
				return ;
			}
			printf("%ld\n", s->data[s->top]);
			free(s);
		}
		else
		{
			printf("Error\n");
			return ;
		}
	}
	else
	{
		printf("Error\n");
		return ;
	}
}
int			main(int argc , char **argv)
{
	char	**tab;
	if (argc == 2)
	{
		tab = ft_strsplit(argv[1], ' ');
		if (!tab)
		{
			printf("Error\n");
			return (0);
		}
		rpn_cal(tab);
	}
	else
		printf("Error\n");
	return (0);
}
