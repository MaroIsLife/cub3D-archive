/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:38:16 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:38:17 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	player_int(int i, int j)
{
	if (g_player.found == 1)
	{
		ft_putstr("Duplicate Players");
		exit(1);
	}
	if (g_data.map[i][j] == 'N')
		g_player.pos = 'N';
	else if (g_data.map[i][j] == 'W')
		g_player.pos = 'W';
	else if (g_data.map[i][j] == 'S')
		g_player.pos = 'S';
	else if (g_data.map[i][j] == 'E')
		g_player.pos = 'E';
}

void	check_map2(int i, int j, double tile_i, double tile_j)
{
	if (g_data.map[i][j] == 'N' | g_data.map[i][j] == 'W'
	|| g_data.map[i][j] == 'S' || g_data.map[i][j] == 'E')
	{
		player_int(i, j);
		if (g_data.map[i][j] == '2')
			g_nsprite++;
		g_player.found = 1;
		if (g_data.map[i][j] == 'N')
			g_player.rotationangle = 270;
		else if (g_data.map[i][j] == 'W')
			g_player.rotationangle = 180;
		else if (g_data.map[i][j] == 'S')
			g_player.rotationangle = 90;
		else if (g_data.map[i][j] == 'E')
			g_player.rotationangle = 0;
		g_player.x = tile_j;
		g_player.y = tile_i;
		g_data.map[i][j] = '0';
	}
	else if (g_data.map[i][j] == '2')
		g_nsprite++;
}

void	check_map(void)
{
	int		i;
	int		j;
	double	tile_i;
	double	tile_j;

	j = 0;
	i = 0;
	while (i < g_data.ver)
	{
		while (j < g_data.hor)
		{
			tile_i = ((double)i + 0.5) * TILE_SIZE;
			tile_j = ((double)j + 0.5) * TILE_SIZE;
			check_map2(i, j, tile_i, tile_j);
			j++;
		}
		j = 0;
		i++;
	}
	if (g_player.found == 0)
	{
		ft_putstr("No Player found");
		exit(1);
	}
}
