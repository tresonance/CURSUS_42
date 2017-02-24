/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:08:10 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:08:16 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if (c < 48)
		return (0);
	else if (c <= 57)
		return (1);
	else if (c < 65)
		return (0);
	else if (c <= 90)
		return (1);
	else if (c < 97)
		return (0);
	else if (c <= 122)
		return (1);
	else
		return (0);
}
