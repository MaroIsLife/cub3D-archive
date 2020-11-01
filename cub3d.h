#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "get_next_line.h"
# include "mlx.h"
# include "time.h"
clock_t begin, end;
#define CLOCK(x) do { \
    begin = clock(); \
    x; \
    end = clock(); \
    printf("time taken: %lfs\n", (double)(end - begin) / CLOCKS_PER_SEC); \
} while (0);

#define TILE_SIZE 64
#define PI 3.14159265358979323846
#define circle_size 10
#define FOV_ANGLE 60
#define INT_MAX 2147483647
#define PLAYER_SPEED 8
#define ROT_SPEED 5




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
	int directionLR;
	double moveSpeed;
	float rotationSpeed;
  float moveStep;
  int found;
}	t_player;

typedef struct s_color {
	int r;
	int g;
	int b;
	int color;

} t_color;

typedef struct s_ray
{
float rayAngle;
float wallhitX;
float wallhitY;
float distance;
float height;
int top;
int bottom;
float offset;
int wasHitVertical;
int isRayFacingUp;
int isRayFacingDown;
int isRayFacingLeft;
int isRayFacingRight;
int wallHitContent;
} t_ray[2550];


typedef struct s_data {
	int reso_one;
	int reso_two;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	char **map;
	char *mapName;
	int mapstart;
	int ver;
	int hor;
	int Fcolor;
	int Ccolor;

}	t_data;

typedef struct s_txt {
  void *ptr[5];
  int *data[5];
  int bpp;
  int line;
  int endian;
  int height[5];
  int width[5];
} t_txt;


typedef struct  s_mg {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	
}               t_mg;

t_ray g_ray;
t_mg g_mg;
t_mlx g_mlx;
t_player g_player;
t_data g_data;
t_txt g_txt;
t_color g_color;




  int		ft_atoi(const char *str);
  void	*ft_calloc(size_t n, size_t size);
  char	**ft_split(const char *s, char c);
  void error_one();
  void error_two();
  void error_three();
  void error_four();
  void error_first_last();
  void error_up_down();
  void error_other();
  void open_txt(char *txt);
  void all_errors();
#endif 
