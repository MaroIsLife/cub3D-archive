#include "cub3d.h"

void int_data()
{
    g_header.width = g_data.reso_one;
    g_header.height = g_data.reso_two;
    g_header.bitcount = 24;
    g_header.width_in_bytes = ((g_header.width * g_header.bitcount + 31) / 32) * 4;
    g_header.imagesize = g_header.width_in_bytes * g_header.height;
    g_header.bisize = 40;
    g_header.bfoffbits = 54;
    g_header.filesize = 54 + g_header.imagesize;
    g_header.biplanes = 1;
}

unsigned char *get_header()
{
    unsigned char *header;

    header = (unsigned char *)ft_calloc(54,sizeof(header));
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

t_rgb	int_rgb(int col)
{
	t_rgb rgb;

	rgb.b = col % 256;
	rgb.g = ((col - rgb.b) / 256) % 256;
	rgb.r = ((col - rgb.b) / (256 * 256)) - (rgb.g / 256);
	return (rgb);
}

void fill_image(unsigned char *buffer,int *data, int col, int row)
{
    t_rgb	rgb;
	int		color_int;

	color_int = data[(g_data.reso_two - row) * g_data.reso_one + col];
	rgb = int_rgb(color_int);
	buffer[row * g_header.width_in_bytes + col * 3 + 0] = rgb.b;
	buffer[row * g_header.width_in_bytes + col * 3 + 1] = rgb.g;
	buffer[row * g_header.width_in_bytes + col * 3 + 2] = rgb.r;

}
void			draw_bmp(unsigned char *buffer)
{
    int fd;

    fd = open("./saved.bmp", O_WRONLY | O_APPEND | O_CREAT, 777);
    if (fd == -1)
    {
        perror("Error\nCannot save");
        exit(1);
    }
    write(fd, get_header(), 54);
    write(fd,(char *)buffer,g_header.imagesize);
    close(fd);
    free(buffer);
}


void save_bitmap()
{
    int *data;
    unsigned char *buffer;
    unsigned char *header;
    int col;
    int row;

    header = get_header();
    buffer = malloc(g_header.imagesize);
    data = (int *)mlx_get_data_addr(g_mg.img,&col,&col,&col);
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