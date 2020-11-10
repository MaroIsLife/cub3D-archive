/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:54:06 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:54:07 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	init_texture2(void)
{
	g_txt.ptr[0] = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.we,
	&g_txt.width[0], &g_txt.height[0]);
	g_txt.ptr[1] = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.ea,
	&g_txt.width[1], &g_txt.height[1]);
	g_txt.ptr[2] = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.no,
	&g_txt.width[2], &g_txt.height[2]);
	g_txt.ptr[3] = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.so,
	&g_txt.width[3], &g_txt.height[3]);
	if (g_txt.ptr[0] == NULL || g_txt.ptr[1] == NULL || g_txt.ptr[2] == NULL
	|| g_txt.ptr[3] == NULL)
	{
		ft_putstr("Error In texture XPM File");
		exit(1);
	}
}

void	init_texture(void)
{
	open_txt(g_data.so);
	open_txt(g_data.no);
	open_txt(g_data.we);
	open_txt(g_data.ea);
	open_txt(g_data.s);
	init_texture2();
	g_txt.data[0] = (int *)mlx_get_data_addr(g_txt.ptr[0], &g_txt.bpp,
	&g_txt.line, &g_txt.endian);
	g_txt.data[1] = (int *)mlx_get_data_addr(g_txt.ptr[1], &g_txt.bpp,
	&g_txt.line, &g_txt.endian);
	g_txt.data[2] = (int *)mlx_get_data_addr(g_txt.ptr[2], &g_txt.bpp,
	&g_txt.line, &g_txt.endian);
	g_txt.data[3] = (int *)mlx_get_data_addr(g_txt.ptr[3], &g_txt.bpp,
	&g_txt.line, &g_txt.endian);
}
