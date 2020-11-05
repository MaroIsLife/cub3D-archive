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


typedef struct s_header
{
	int	width;
	int	height;
	int	bitcount;
	int	width_in_bytes;
	int	imagesize;
	int	bisize;
	int	bfoffbits;
	int	filesize;
	int	biplanes;
} t_header;


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
  int saved;
}	t_player;

typedef struct s_color {
	int r;
	int g;
	int b;
	int color;

} t_color;

typedef struct	s_sprite {
	float x;
	float y;
	float dst;
	float size;
	float x_ofst;
	float y_ofst;
}				t_sprite[3500];

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
int wallHitContent;
int isRayFacingUp;
int isRayFacingDown;
int isRayFacingLeft;
int isRayFacingRight;
float	hitx;
float	hity;
} t_ray[3500];


typedef struct	s_var{

	float	nexthitx;
	float	nexthity;
	float	hitx1;
	float	hitx2;
	float	hity1;
	float	hity2;
	float	xstep;
	float	ystep;
	float	xtocheck;
	float	ytocheck;
	float	distanceHor;
	float	distanceVer;
	float	distance;
	float	xintercept;
	float	yintercept;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
}				t_var;


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

typedef struct	s_sptexture
{
	void	*img_sprite;
	int		*data;
	int		width;
	int		height;
}				t_sptexture;


typedef struct  s_mg {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	
}               t_mg;

typedef struct	s_rgb{
	int		r;
	int		g;
	int		b;
}				t_rgb;

t_ray g_ray;
t_mg g_mg;
t_mlx g_mlx;
t_player g_player;
t_data g_data;
t_txt g_txt;
t_color g_color;
t_header g_header;
t_sprite g_sprite;
int		g_nsprite;
t_sptexture g_sptexture;
t_var g_var;
int g_rgbcounter;



void    my_mlx_pixel_put(t_mg *data, int x, int y, int color);
  int	ft_atoi(const char *str);
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
  void	*ft_memcpy(void *dst, const void *src, size_t n);
  void int_data();
unsigned char *get_header();
  void save_bitmap();
  t_rgb	int_rgb(int col);
  void fill_image(unsigned char *buffer,int *data, int col, int row);
  void draw_bmp(unsigned char *buffer);
  int		is_wall(float x, float y);


  int		len(char *s);
  void	sort(void);
  void	save_cordinate(int i, int j, int id);
  void get_sprite_pos();
  void	get_spriteimage();
  void	sprite_put_pixels(int id, int i, int j);
  void	draw_sprite(int id);
  void render_sprite(int id);
  float	to_deg(float angle);
  float	to_rad(float angle);




  void cast(float rayAngle,int id);
  void calc_dis(float rayAngle,int id);
  void v_cast(float rayAngle);
	void h_cast(float rayAngle);
	void v_calc();
	void h_calc();
	  float normalizeAngle(float angle);
	void arg_save_check(char *save);
	void  arg_check(char *s1);
	void  arg_check2(char *s1, char **s2);
	int keyRelease(int key);
	int keyPress(int key);
	int red();
	void get_settings_texture(char **content,int ab);
	 void get_settings();
	 int getarray(char **content, int ab, int aa);
	  char *get_texture(char **content, int ab);
	  void get_resolution(char **content, int ab);
	    char **get_line();
		int get_color(char **content, int ab);
		void get_colorR(char **content, int b,int i,int ab);
	void get_colorG(char **content, int b,int i,int ab);
	void get_colorB_error(char **content, int b,int i,int ab);
		  void int_map(char **content);
#endif 
