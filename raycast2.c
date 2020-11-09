/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:17:14 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:17:15 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	wall_data(int id)
{
	int		top;
	float	distance;
	float	projection;
	float	wallheight;
	int		bottom;

	distance = g_ray[id].distance *
	cos((g_ray[id].rayangle - g_player.rotationangle) * (M_PI / 180));
	projection = (g_data.reso_one / 2) / tan((60 / 2) * (M_PI / 180));
	wallheight = (TILE_SIZE / distance) * projection;
	top = (g_data.reso_two / 2) - ((int)wallheight / 2);
	bottom = top + wallheight;
	g_ray[id].top = top;
	g_ray[id].bottom = bottom;
	g_ray[id].height = wallheight;
}

void	draw_floor(int id)
{
	int i;

	i = 0;
	while (i < g_ray[id].top)
	{
		my_mlx_pixel_put(&g_mg, id, i, g_data.ccolor);
		i++;
	}
	i = g_ray[id].bottom;
	while (i < g_data.reso_two)
	{
		my_mlx_pixel_put(&g_mg, id, i, g_data.fcolor);
		i++;
	}
}
