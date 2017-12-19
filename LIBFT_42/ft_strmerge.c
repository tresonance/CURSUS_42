/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 07:09:48 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 07:09:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char *s1, char *s2)
{
	char *str;

	str = ft_strjoin((const char*)s1, (const char*)s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	s1 = NULL;
	s2 = NULL;
	return (str);
}
