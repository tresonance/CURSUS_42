/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:24:41 by kmjaku            #+#    #+#             */
/*   Updated: 2017/12/15 14:35:12 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define GTK_HEIGHT 220
#define GTK_WIDTH 150

int				scene_rt(char *filename)
{
	const char	*tab[11] = {"compose.rt", "paraboloide.rt",
		"box.rt", "negatif.rt", "sphere.rt", "torus.rt",
		"triangle.rt", "rtv1.rt", "decoupe.rt", "bump.rt", NULL};
	int			i;
	char		*s;

	if (filename != NULL)
	{
		i = -1;
		while (tab[++i] != NULL)
		{
			s = ft_strstr(filename, tab[i]);
			if (s && ft_strcmp(s, tab[i]) == 0)
				return (1);
		}
	}
	return (0);
}

void			gtk_dialog(t_scene *e, gpointer data)
{
	GtkWidget	*dialog;
	gchar		*filename;
	gint		response;

	(void)e;
	dialog = gtk_file_chooser_dialog_new("Open", GTK_WINDOW(data),
		GTK_FILE_CHOOSER_ACTION_OPEN, ("_Open"), GTK_RESPONSE_OK,
		"_Cancel", GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show(dialog);
	response = gtk_dialog_run(GTK_DIALOG(dialog));
	if ((response == GTK_RESPONSE_OK) &&
		(filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog))))
	{
		destroy(dialog, data);
		if ((filename != NULL) && (scene_rt(filename) == 1))
			rt_launch(filename);
		g_free(filename);
		ft_putstr("File doesn't exist\n");
	}
	else
		gtk_widget_destroy(dialog);
}

gchar			*name_of_members(void)
{
	gchar		*label_content;

	label_content = "<b>L'équipe :</b>"
		" <span foreground=\"#2990ea\">\n\n kmjaku,"
		"\n brel-baz,\n thchin,\n ibtraore\n\n</span>"
		" <b>Vous présente</b> <b><span foreground=\"#a31a28\">RT</span></b>";
	return (label_content);
}

int				gtk_launch(int ac, char **av)
{
	t_scene		e;

	gtk_init(&ac, &av);
	gtk_window_create(&e, GTK_WIDTH, GTK_HEIGHT, "RT");
	g_signal_connect(G_OBJECT(e.gtk.window), "destroy",
		G_CALLBACK(gtk_main_quit), e.gtk.window);
	gtk_layout(&e.gtk);
	gtk_widget_show_all(e.gtk.window);
	gtk_main();
	return (0);
}
