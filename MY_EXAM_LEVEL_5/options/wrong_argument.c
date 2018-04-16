#include "header.h"

int						ft_strlen(char *str)
{
	int					len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

int						is_char_inside(char *str, char c)
{
	unsigned int		i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			is_wrong_argument(char *arg)
{
	int		i;

	if (arg[0] != '-')
		return (1);
	i = 1;
	while(arg[i])
	{
		if (!is_char_inside("abcdefghijklmnopqrstuvwxyz", arg[i])
			&& !is_char_inside("ABCDEFGHIJKLMNOPQRSTUVWXYZ", arg[i]))
			return (2);
		i++;
	}
	if (i == 1)
		return (1);
	return (0);
}

int						are_wrong_parameter(char **argv)
{
	int					i;

	i = 1;
	while(argv[i])
	{
		if(ft_strlen(argv[i]) > 4)
			return(1);
		if( 2 == is_wrong_argument(argv[i]))
			return (2);
		if( 1 == is_wrong_argument(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
