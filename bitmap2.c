/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:24:06 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/08 23:24:07 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void			int_data(void)
{
	g_header.width = g_data.reso_one;
	g_header.height = g_data.reso_two;
	g_header.bitcount = 24;
	g_header.width_in_bytes = ((g_header.width *
	g_header.bitcount + 31) / 32) * 4;
	g_header.imagesize = g_header.width_in_bytes * g_header.height;
	g_header.bisize = 40;
	g_header.bfoffbits = 54;
	g_header.filesize = 54 + g_header.imagesize;
	g_header.biplanes = 1;
}

unsigned char	*get_header(void)
{
	unsigned char *header;

	header = (unsigned char *)ft_calloc(54, sizeof(header));
	int_data();
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &g_header.filesize, 4);
	ft_memcpy(header + 10, &g_header.bfoffbits, 4);
	ft_memcpy(header + 14, &g_header.bisize, 4);
	ft_memcpy(header + 18, &g_header.width, 4);
	ft_memcpy(header + 22, &g_header.height, 4);
	ft_memcpy(header + 26, &g_header.biplanes, 2);
	ft_memcpy(header + 28, &g_header.bitcount, 2);
	ft_memcpy(header + 34, &g_header.imagesize, 4);
	return (header);
}

t_rgb			int_rgb(int col)
{
	t_rgb rgb;

	rgb.b = col % 256;
	rgb.g = ((col - rgb.b) / 256) % 256;
	rgb.r = ((col - rgb.b) / (256 * 256)) - (rgb.g / 256);
	return (rgb);
}
