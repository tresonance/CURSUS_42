/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 23:27:22 by brel-baz          #+#    #+#             */
/*   Updated: 2016/11/15 04:23:08 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((((unsigned char*)s1)[i] == ((unsigned char*)s2)[i]) &&
			(((unsigned char*)s1)[i]) && (((unsigned char*)s2)[i]))
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
