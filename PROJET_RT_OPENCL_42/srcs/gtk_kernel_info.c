/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_kernel_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:54:32 by kmjaku            #+#    #+#             */
/*   Updated: 2017/12/15 13:55:03 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GtkWidget			*get_live_info(t_scene *e, char *info)
{
	char			*content;
	char			copy_concat[50];
	char			ms[50];
	char			*all_in_one;
	GtkWidget		*label;

	ft_strcpy(copy_concat, info);
	content = ft_strcat(copy_concat, convert(e, 1.0f / e->frametime));
	ft_strcpy(ms, content);
	all_in_one = ft_strcat(ms, " fps");
	label = gtk_label_new(all_in_one);
	return (label);
}

GtkWidget			*get_live_time_info_1(t_scene *e, char *info)
{
	char			*content;
	char			*all_in_one;
	char			copy_concat[50];
	char			ms[50];
	GtkWidget		*label;

	ft_strcpy(copy_concat, info);
	content = ft_strcat(copy_concat, convert(e, e->total_time_1 / 10000));
	ft_strcpy(ms, content);
	all_in_one = ft_strcat(ms, " ms");
	label = gtk_label_new(all_in_one);
	return (label);
}

GtkWidget			*get_live_time_info_2(t_scene *e, char *info)
{
	char			*content;
	char			*all_in_one;
	char			copy_concat[50];
	char			ms[50];
	GtkWidget		*label;

	ft_strcpy(copy_concat, info);
	content = ft_strcat(copy_concat, convert(e, e->total_time_2));
	ft_strcpy(ms, content);
	all_in_one = ft_strcat(ms, " ms");
	label = gtk_label_new(all_in_one);
	return (label);
}
