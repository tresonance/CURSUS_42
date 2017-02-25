/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musique.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 04:06:31 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 10:02:07 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		musics_groupe1(int key)
{
	if (key == MUSIK_1)
	{
		system("afplay musics/song.mp3&");
	}
	if (key == MUSIK_2)
	{
		system("afplay musics/ff1.mp3&");
	}
	if (key == MUSIK_3)
	{
		system("afplay musics/ff7.mp3&");
	}
	if (key == MUSIK_4)
	{
		system("afplay musics/zelda.mp3&");
	}
}

void		musics_groupe2(int key)
{
	if (key == MUSIK_5)
	{
		system("afplay musics/final_battle.mp3&");
	}
	if (key == MUSIK_6)
	{
		system("afplay musics/nyan.mp3&");
	}
	if (key == MUSIK_7)
	{
		system("afplay musics/tetris.mp3&");
	}
	if (key == MUSIK_8)
	{
		system("afplay musics/mario.mp3&");
	}
}

void		musics_groupe3(int key)
{
	if (key == MUSIK_9)
	{
		system("afplay musics/birds.mp3&");
	}
	if (key == MUSIK_0)
	{
		system("afplay musics/kart.mp3&");
	}
	if (key == ESC)
	{
		system("afplay musics/exit.mp3");
		exit(0);
	}
}

int			play_music(int key)
{
	static int kill = 0;
	if (kill)
		system("killall afplay");
	kill = 1;
	musics_groupe1(key);
	musics_groupe2(key);
	musics_groupe3(key);
	return (0);
}
