/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:43:10 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/18 22:43:22 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_putchar(char c);

void		ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void		ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

void		taille_norm(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		ft_putstr(av[i]);
		ft_putchar('\n');
		i++;
	}
}

int			main(int argc, char **argv)
{
	int i;
	int j;

	(void)argc;
	i = 0;
	j = 1;
	if (argc > 1)
	{
		while (j == 1)
		{
			j = 0;
			while (argv[++i + 1])
			{
				if (ft_strcmp(argv[i], argv[i + 1]) > 0)
				{
					ft_swap(&argv[i], &argv[i + 1]);
					j = 1;
				}
			}
			i = 0;
		}
		taille_norm(&argv[i]);
	}
	else
		return (0);
}
