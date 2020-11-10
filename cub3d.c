/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:52:34 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:52:35 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	my_mlx_pixel_put(t_mg *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x < g_data.reso_one && y < g_data.reso_two && x > 0 && y > 0)
		*(unsigned int*)dst = color;
}

void	update2(void)
{
	double fakex;
	double fakey;

	g_player.rotationangle += g_player.turndirection * g_player.rotationspeed;
	g_player.rotationangle = fmod(g_player.rotationangle, 360);
	g_player.movestep = g_player.walkdirection * g_player.movespeed;
	fakex = g_player.x + cos((g_player.rotationangle + g_player.directionlr)
	* (M_PI / 180)) * (g_player.movestep * 8);
	fakey = g_player.y + sin((g_player.rotationangle + g_player.directionlr)
	* (M_PI / 180)) * (g_player.movestep * 8);
	if (is_wall1(fakex, fakey) != 1)
	{
		g_player.x += cos((g_player.rotationangle + g_player.directionlr) *
		(M_PI / 180)) * (g_player.movestep);
		g_player.y += sin((g_player.rotationangle + g_player.directionlr)
		* (M_PI / 180)) * (g_player.movestep);
	}
}

int		update(void)
{
	if (g_player.saved == 0)
	{
		mlx_hook(g_mlx.win_ptr, 2, 0, keypress, 0);
		mlx_hook(g_mlx.win_ptr, 3, 0, keyrelease, 0);
		mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	}
	update2();
	castallrays();
	if (g_player.saved == 0)
		mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
	if (g_player.saved == 1)
	{
		save_bitmap();
		exit(0);
	}
	mlx_destroy_image(g_mlx.mlx_ptr, g_mg.img);
	g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
	g_mg.addr = mlx_get_data_addr(g_mg.img,
	&g_mg.bits_per_pixel, &g_mg.line_length, &g_mg.endian);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 2 || argc == 3)
	{
		arg_check(argv[1]);
		if (argc == 3)
			arg_save_check(argv[2]);
		get_settings();
		playersettings();
		g_mlx.mlx_ptr = mlx_init();
		if (g_player.saved == 0)
			g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_data.reso_one,
			g_data.reso_two, "cub3D");
		g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one,
		g_data.reso_two);
		g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel,
		&g_mg.line_length, &g_mg.endian);
		check_map();
		all_errors();
		mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
		if (g_player.saved == 0)
			mlx_hook(g_mlx.win_ptr, 17, 0, red, (void *)0);
		mlx_loop(g_mlx.mlx_ptr);
	}
	else
		ft_putstr("Please insert the map's name.");
	return (0);
}
