#include "header.h"

int					main(int argc, char **argv)
{
	char			error_msg[] = "options: abcdefghijklmnopqrstuvwxyz";
	int				error_value;

	if(argc > 1)
	{
		error_value = are_wrong_parameter(argv);
		if(error_value == 1)
			write(1, error_msg, ft_strlen(error_msg));
		else if (error_value == 2)
			write(1, "Invalid Option", 14);
		else
			options(argc, argv);
	}
	else
		write(1, "Invalid Option", 14);
	write(1, "\n", 1);
	return (0);
}
