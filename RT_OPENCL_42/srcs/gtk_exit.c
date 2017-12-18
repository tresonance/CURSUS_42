/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:52:39 by kmjaku            #+#    #+#             */
/*   Updated: 2017/12/14 03:42:16 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	destroy(GtkWidget *widget, gpointer data)
{
	(void)widget;
	gtk_widget_destroy(data);
}

void	destroy_exit(GtkWidget *widget, gpointer data)
{
	(void)widget;
	gtk_widget_destroy(data);
	g_print("See you Later\n");
	exit(1);
}
