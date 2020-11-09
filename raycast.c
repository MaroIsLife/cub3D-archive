/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:17:19 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:17:20 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	draw_wall(int id, int nb)
{
	float	a;
	float	b;
	int		o;
	float	f;
	float	i;

	o = 0;
	i = 0.;
	a = g_ray[id].top;
	b = g_ray[id].bottom;
	f = (float)g_txt.height[nb] / g_ray[id].height;
	while (a < b)
	{
		if ((int)i * g_txt.width[nb] + (int)g_ray[id].offset
		< g_txt.width[nb] * g_txt.height[nb] && id >= 0)
		{
			my_mlx_pixel_put(&g_mg, id, a, g_txt.data[nb][(int)(i)
			* g_txt.width[nb] + (int)g_ray[id].offset]);
		}
		a++;
		i += f;
	}
}

int		direction(int nb, int id)
{
	if (g_ray[id].washitvertical == 1)
	{
		if (g_ray[id].israyfacingleft == 1)
			nb = 0;
		if (g_ray[id].israyfacingright == 1)
			nb = 1;
	}
	if (g_ray[id].washitvertical == 0)
	{
		if (g_ray[id].israyfacingup == 1)
			nb = 2;
		if (g_ray[id].israyfacingdown == 1)
			nb = 3;
	}
	return (nb);
}

void	castallrays2(int nb)
{
	int id;

	id = 0;
	while (id < g_data.reso_one)
	{
		wall_data(id);
		id++;
	}
	init_texture();
	id = 0;
	while (id < g_data.reso_one)
	{
		nb = direction(nb, id);
		draw_floor(id);
		draw_wall(id, nb);
		id++;
	}
	id = 0;
	get_sprite_pos();
	get_spriteimage();
	while (id < g_nsprite)
	{
		render_sprite(id);
		id++;
	}
}

void	castallrays(void)
{
	int		id;
	float	rayangle;
	int		nb;

	id = 0;
	nb = 0;
	rayangle = g_player.rotationangle - (60 / 2);
	while (id < g_data.reso_one)
	{
		cast(rayangle, id);
		rayangle += 60.0 / (float)g_data.reso_one;
		id++;
	}
	castallrays2(nb);
}
