/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:52:13 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:52:16 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

int		is_wall1(float x, float y)
{
	if ((int)x >= g_data.hor * TILE_SIZE || (int)x <= 0 ||
	(int)y >= g_data.ver * TILE_SIZE || (int)y <= 0)
		return (1);
	return (g_data.map[(int)floor(y / TILE_SIZE)][(int)
		floor(x / TILE_SIZE)] - '0');
}

int		is_wall(float x, float y)
{
	int mapx;
	int mapy;

	mapx = (int)floor(x / TILE_SIZE);
	mapy = (int)floor(y / TILE_SIZE);
	if (mapx >= 0 && mapy >= 0 && mapy
	< g_data.ver && mapx < len(g_data.map[mapy]))
	{
		if (g_data.map[mapy][mapx] != '1')
			return (1);
	}
	return (0);
}

void	playersettings(void)
{
	g_player.radius = 3;
	g_player.turndirection = 0;
	g_player.walkdirection = 0;
	g_player.movespeed = 8;
	g_player.rotationspeed = 3;
	if (g_data.reso_one > 2560)
		g_data.reso_one = 2560;
	if (g_data.reso_two > 1440)
		g_data.reso_two = 1440;
	if (g_data.reso_one <= 0 || g_data.reso_two <= 0)
	{
		ft_putstr("Error\n Resolution");
		exit(1);
	}
}
