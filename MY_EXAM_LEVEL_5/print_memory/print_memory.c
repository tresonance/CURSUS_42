/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 03:38:28 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/04 04:53:21 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void			print_hexa(int val, int rem)
{
	char base[] = "0123456789abcdef";
	if (rem > 1)
		print_hexa(val >> 4, rem - 1);
	write (1, base + (val%16), 1);
}

void			print_num(const void *addr, size_t i, size_t size)
{
	size_t a;
	
	a = 0;

	while (a < 16 && (a + i) < size)
	{
			print_hexa(*((const unsigned char*)(addr + a + i)), 2);
		if (a % 2)
			write (1, " ", 1);
		a++;
	}
	while (a < 16)
	{
			write (1, "  ", 2);
		if (a % 2)
			write(1, " ", 1);
		a++;
	}

}

void		print_char(const void *addr , size_t i, size_t size)
{
	size_t a;
	unsigned char c;

	a = 0;
	while (a < 16  && (a + i) < size)
	{
		c = *((const unsigned char *)(addr + a + i));
		if (' ' <= c  && c <= '~')
			write (1, &c, 1);
		else
			write (1,".", 1);
		a++;
	}
}

void print_memory(const void *addr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		print_num(addr , i, size);
		print_char(addr, i, size);
		write (1, "\n", 1);
		i += 16;
	}
}

