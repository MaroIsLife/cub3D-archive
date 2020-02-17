#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"

#define map_rows 23
#define map_cols 27
#define tile_size 32
#define RED 0xff0000
#define WHITE 0xffffff
#define GOLD 0xffd700
#define BLUE 0x0000ff
#define AQUA 0x00ffff


typedef struct s_mlx {
		void *mlx_ptr;
		void *win_ptr;
}	t_mlx;

t_mlx g_mlx;

typedef struct s_data {
	int reso_one;
	int reso_two;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	char **map;
	int ver;
	int hor;

}	t_data;
t_data g_data;
#endif 