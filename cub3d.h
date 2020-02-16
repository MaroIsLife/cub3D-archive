#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"

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