#ifndef __HEADER_H__
#define __HEADER_H__

#include <unistd.h>
#define INTEGER_SIZE 32
#define OCTET_SIZE 8

/*
 * wrong_argument.c
 */
int					are_wrong_parameter(char **argv);
int					ft_strlen(char *str);

/*
 * utils.c
 */
void				init_bits(char *init_octet);
void				print_bits(char *init_octet);
void				options(int argc, char **argv);
#endif
