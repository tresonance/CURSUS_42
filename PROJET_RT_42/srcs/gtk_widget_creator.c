/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_widget_creator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:15:29 by kmjaku            #+#    #+#             */
/*   Updated: 2017/12/14 22:08:11 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define GTK_HEIGHT 240
#define GTK_WIDTH 150

void			gtk_window_create(t_scene *e, gint width, gint height,
				gchar *title)
{
	GtkWidget	*window;

	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	e->gtk.window = window;
}

void			gtk_menu(t_gtk *e)
{
	GtkWidget	*menu_bar;
	GtkWidget	*menu;
	GtkWidget	*menu_item;

	menu_bar = gtk_menu_bar_new();
	menu = gtk_menu_new();
	menu_item = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
	menu_item = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
	g_signal_connect(G_OBJECT(menu_item), "activate",
		G_CALLBACK(gtk_dialog), e->window);
	menu_item = gtk_menu_item_new_with_mnemonic("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
	g_signal_connect(G_OBJECT(menu_item), "activate",
		G_CALLBACK(destroy_exit), e->window);
	e->menu_bar = menu_bar;
}

void			gtk_layout(t_gtk *e)
{
	e->layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->window), e->layout);
	e->image = gtk_image_new_from_file("image/gtk_bg.jpg");
	gtk_layout_put(GTK_LAYOUT(e->layout), e->image, 0, 23);
	gtk_menu(e);
	gtk_layout_put(GTK_LAYOUT(e->layout), e->menu_bar, 0, 0);
	e->label = gtk_label(name_of_members());
	gtk_layout_put(GTK_LAYOUT(e->layout), e->label, GTK_WIDTH / 3, 30);
	e->button_open = gtk_button("Open");
	gtk_layout_put(GTK_LAYOUT(e->layout), e->button_open, GTK_WIDTH / 3, 135);
	g_signal_connect(G_OBJECT(e->button_open), "clicked",
		G_CALLBACK(gtk_dialog), e->window);
	e->button_quit = gtk_button("Close");
	gtk_layout_put(GTK_LAYOUT(e->layout), e->button_quit, GTK_WIDTH / 3, 170);
	g_signal_connect(G_OBJECT(e->button_quit), "clicked",
		G_CALLBACK(destroy_exit), e->window);
}

GtkWidget		*gtk_label(gchar *label_content)
{
	GtkWidget	*label;

	label = gtk_label_new(label_content);
	gtk_label_set_markup(GTK_LABEL(label), label_content);
	return (label);
}

GtkWidget		*gtk_button(gchar *button_name)
{
	GtkWidget	*button;

	button = gtk_button_new_with_label(button_name);
	return (button);
}
