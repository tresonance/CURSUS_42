#include "biggest_pal.h"


#include <stdio.h>
int					is_palindrome(char *str, int start, int end);


int					main(int argc, char **argv)
{
	if(argc == 2)
	{
		biggest_palindrome(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
