#include "biggest_pal.h"

int					ft_strlen(char *str)
{
	int				len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void				ft_putstr(char *str)
{
	int				i;

	i = 0;
	while(str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}

void				print_biggest(char *str, int len)
{
	int				i;

	i = -1;
	while(++i < len && str[i])
		write(1, str + i, 1);
}

int					is_palindrome(char *str, int i)
{
	
	if (ft_strlen(str + i) <= 1)
		return (TRUE);
	return(((str + i)[0] == str[ft_strlen(str + i) - 1]) && is_palindrome(str , i + 1));
}

void				biggest_palindrome(char *str)
{
	int				i;
	int				j;
	char			*biggest;
	int				max_len;
	int				biggest_len;

	i = 0;
	max_len = 0;
	while(str[i])
	{
		j = 0;
		while (str[i + j])
		{
			if(is_palindrome(str, i + j))
			{
				if(max_len < j + 1)
				{
					biggest = str + i + j;
					max_len = j;
				}
			}
			j++;
		}
		i++;
	}
	print_biggest(biggest, max_len);
}
