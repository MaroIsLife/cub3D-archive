/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:55:46 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:55:46 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		len(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	sort(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < g_nsprite)
	{
		j = -1;
		while (++j < g_nsprite - i)
		{
			if (g_sprite[j].dst < g_sprite[j + 1].dst)
			{
				tmp[0] = g_sprite[j];
				g_sprite[j] = g_sprite[j + 1];
				g_sprite[j + 1] = tmp[0];
			}
		}
	}
}

void	save_cordinate(int i, int j, int id)
{
	g_sprite[id].x = j * TILE_SIZE + 30;
	g_sprite[id].y = i * TILE_SIZE + 30;
	g_sprite[id].dst = (float)sqrt((g_sprite[id].x - g_player.x) *
			(g_sprite[id].x - g_player.x) +
			(g_sprite[id].y - g_player.y) *
			(g_sprite[id].y - g_player.y));
}

void	get_sprite_pos(void)
{
	int i;
	int j;
	int id;

	i = 0;
	id = 0;
	while (i < g_data.ver)
	{
		j = 0;
		while (j < len(g_data.map[i]))
		{
			if (g_data.map[i][j] == '2')
			{
				save_cordinate(i, j, id);
				id++;
			}
			j++;
		}
		i++;
	}
	sort();
}
