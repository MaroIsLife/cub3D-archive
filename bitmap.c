/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:20:10 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/08 23:21:54 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	fill_image(unsigned char *buffer, int *data, int col, int row)
{
	t_rgb	rgb;
	int		color_int;

	color_int = data[(g_data.reso_two - row) * g_data.reso_one + col];
	rgb = int_rgb(color_int);
	buffer[row * g_header.width_in_bytes + col * 3 + 0] = rgb.b;
	buffer[row * g_header.width_in_bytes + col * 3 + 1] = rgb.g;
	buffer[row * g_header.width_in_bytes + col * 3 + 2] = rgb.r;
}

void	draw_bmp(unsigned char *buffer)
{
	int fd;

	fd = open("./saved.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		error_msg();
	write(fd, get_header(), 54);
	write(fd, (char *)buffer, g_header.imagesize);
	close(fd);
	free(buffer);
}

void	save_bitmap(void)
{
	int				*data;
	unsigned char	*buffer;
	unsigned char	*header;
	int				col;
	int				row;

	header = get_header();
	buffer = malloc(g_header.imagesize);
	data = (int *)mlx_get_data_addr(g_mg.img, &col, &col, &col);
	row = g_data.reso_two - 1;
	while (row >= 0)
	{
		col = 0;
		while (col < g_data.reso_one)
		{
			fill_image(buffer, data, col, row);
			col++;
		}
		row--;
	}
	draw_bmp(buffer);
}
