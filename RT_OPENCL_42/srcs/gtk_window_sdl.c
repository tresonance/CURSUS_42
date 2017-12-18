/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_window_sdl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 05:29:27 by kmjaku            #+#    #+#             */
/*   Updated: 2017/12/15 13:55:48 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				free_s(char **s, char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	free(s);
}

char				*convert(t_scene *e, double nb)
{
	char			**str;
	char			*copy;

	e->p_entiere = (int)nb;
	str = (char**)malloc(sizeof(char*) * 3);
	str[1] = (char*)malloc(sizeof(char) * 2);
	if (!(copy = (char*)malloc(sizeof(char) * 10)))
		return (NULL);
	e->p_decimale = (nb - e->p_entiere) * 10000;
	str[0] = ft_itoa(e->p_entiere);
	str[1][0] = '.';
	str[1][1] = '\0';
	str[2] = ft_itoa((int)e->p_decimale);
	e->i = -1;
	e->k = -1;
	while (++e->i < 3)
	{
		e->j = -1;
		while (str[e->i][++e->j])
			copy[++e->k] = str[e->i][e->j];
	}
	copy[e->k] = '\0';
	free_s(str, str[0], str[1], str[2]);
	return (copy);
}

void				gtk_window_sdl(t_scene *e)
{
	GtkWidget		*window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "RT INFO");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	e->gtk.window = window;
}

void				layout_put(t_scene *e, int i)
{
	e->gtk.label = get_live_info(e, "Frame per Second : ");
	gtk_layout_put(GTK_LAYOUT(e->gtk.layout), e->gtk.label, 10, i);
	e->gtk.label = get_live_time_info_1(e, "Kernel Execution Time : ");
	gtk_layout_put(GTK_LAYOUT(e->gtk.layout), e->gtk.label, 220, i);
	e->gtk.label = get_live_time_info_2(e, "Read-out Time : ");
	gtk_layout_put(GTK_LAYOUT(e->gtk.layout), e->gtk.label, 450, i);
}

void				window_sdl(t_scene *e, int i)
{
	if (i >= 600)
	{
		gtk_widget_destroy(e->gtk.layout);
		e->gtk.layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(e->gtk.window), e->gtk.layout);
	}
	if (e->gtk.window == NULL)
	{
		gtk_window_sdl(e);
		g_signal_connect(G_OBJECT(e->gtk.window), "destroy",
			G_CALLBACK(destroy_exit), e->gtk.window);
	}
	if (e->gtk.layout == NULL)
	{
		e->gtk.layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(e->gtk.window), e->gtk.layout);
	}
	layout_put(e, i);
	gtk_widget_show_all(e->gtk.window);
}
