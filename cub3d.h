#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"
# include "mlx.h"

#define MAP_VER 23
#define MAP_HOR 27
#define TILE_SIZE 32
#define RED 0xff0000
#define WHITE 0xffffff
#define GOLD 0xffd700
#define BLUE 0x0000ff
#define AQUA 0x00ffff
#define PI 3.14159265358979323846
#define circle_size 10
#define FOV_ANGLE 60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 4



typedef struct s_mlx {
		void *mlx_ptr;
		void *win_ptr;
}	t_mlx;


typedef struct s_player {
	double x;
  double y;
	int radius;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	double moveSpeed;
	float rotationSpeed;
  float moveStep;
}	t_player;



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


typedef struct  s_mg {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_mg;

t_mg g_mg;
t_mlx g_mlx;
t_player g_player;
t_data g_data;





int map[23][27] =  { 
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
  {1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1},
  {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
  {1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  };


  int		ft_atoi(const char *str);
  void			*ft_calloc(size_t n, size_t size);
#endif 