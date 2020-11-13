/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:57:56 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:57:56 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_spriteimage(void)
{
	g_sptexture.img_sprite = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.s,
			&g_sptexture.width, &g_sptexture.height);
	if (g_sptexture.img_sprite == NULL)
	{
		ft_putstr("Error\n in Sprite XPM");
		exit(1);
	}
}

void	sprite_put_pixels(int id, int i, int j)
{
	int *add;
	int a;
	int color;

	add = (int*)mlx_get_data_addr(g_sptexture.img_sprite, &a, &a, &a);
	color = add[((int)g_sptexture.width * (j * (int)g_sptexture.height /
			(int)g_sprite[id].size)) + (i * (int)g_sptexture.width /
			(int)g_sprite[id].size)];
	if (color != 0)
	{
		my_mlx_pixel_put(&g_mg, g_sprite[id].x_ofst + i,
				g_sprite[id].y_ofst + j, color);
	}
}

void	draw_sprite(int id)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < g_sprite[id].size - 1)
	{
		if (g_sprite[id].x_ofst + i < 0 ||
				g_sprite[id].x_ofst + i > g_data.reso_one)
			continue;
		if (g_sprite[id].dst > g_ray[(int)g_sprite[id].x_ofst + i].distance)
			continue;
		j = -1;
		while (++j < g_sprite[id].size - 1)
		{
			if (g_sprite[id].y_ofst + j < 0 ||
					g_sprite[id].y_ofst + j > g_data.reso_two)
				continue;
			sprite_put_pixels(id, i, j);
		}
	}
}

void	render_sprite(int id)
{
	float angle;

	angle = atan2(g_sprite[id].y - g_player.y, g_sprite[id].x - g_player.x);
	while (angle - to_rad(g_player.rotationangle) > M_PI)
		angle -= 2 * M_PI;
	while (angle - to_rad(g_player.rotationangle) < -M_PI)
		angle += 2 * M_PI;
	angle = angle - to_rad(g_player.rotationangle);
	angle = to_deg(angle);
	g_sprite[id].size = (g_data.reso_one / g_sprite[id].dst) * TILE_SIZE;
	g_sprite[id].y_ofst = (g_data.reso_two / 2) - (g_sprite[id].size / 2);
	g_sprite[id].x_ofst = ((angle * g_data.reso_one) / 60) +
		((g_data.reso_one / 2) - (g_sprite[id].size / 2));
	draw_sprite(id);
}
