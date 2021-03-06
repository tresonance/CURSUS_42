/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 07:14:08 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/19 08:37:44 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
			|| c == '\f' || c == '\v');
}
