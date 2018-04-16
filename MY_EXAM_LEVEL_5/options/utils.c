#include "header.h"

void			init_bits(char *int_octet)
{
	int			i;

	i = 0;
	while(i < INTEGER_SIZE)
	{
		int_octet[i] = '0';
		i++;
	}
}

void			print_bits(char *int_octet)
{
	int			i;
	int			j;

	i = 0;
	j = 1;
	while(i < INTEGER_SIZE)
	{
		write(1, &int_octet[i], 1);
		if (j == OCTET_SIZE)
		{
			write(1, " ", 1);
			j = 0;
		}
		i++;
		j++;
	}
}

void			fill_bits(int argc, char **argv, char *int_octet)
{
	int			i;
	int			j;
	int			k;

	i = 1;
	k = (int)INTEGER_SIZE - 1;
	while(i < argc)
	{
		j = 1;
		while(argv[i][j])
		{
			int_octet[(int)INTEGER_SIZE - 1 - (int)(argv[i][j] - 'a')] = '1';
			j++;
		}
		i++;
	}
}

void			options(int argc, char **argv)
{
	char		int_octet[INTEGER_SIZE];

	init_bits(&int_octet[0]);
	fill_bits(argc, argv, &int_octet[0]);
	print_bits(&int_octet[0]);
}
