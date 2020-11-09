/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:21:57 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:21:58 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

int		keypress(int key)
{
	if (key == 13)
		g_player.walkdirection = 1;
	if (key == 2)
	{
		g_player.directionlr = 90;
		g_player.walkdirection = 1;
	}
	if (key == 0)
	{
		g_player.directionlr = 270;
		g_player.walkdirection = 1;
	}
	if (key == 1)
		g_player.walkdirection = -1;
	if (key == 123)
		g_player.turndirection = -1;
	if (key == 124)
		g_player.turndirection = 1;
	if (key == 53)
	{
		mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
		exit(1);
	}
	return (0);
}

int		keyrelease(int key)
{
	if (key == 13)
		g_player.walkdirection = 0;
	if (key == 1)
		g_player.walkdirection = 0;
	if (key == 2)
	{
		g_player.directionlr = 0;
		g_player.walkdirection = 0;
	}
	if (key == 0)
	{
		g_player.directionlr = 0;
		g_player.walkdirection = 0;
	}
	if (key == 123)
		g_player.turndirection = 0;
	if (key == 124)
		g_player.turndirection = 0;
	return (0);
}

int		red(void)
{
	exit(1);
}
