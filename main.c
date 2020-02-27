# include "mlx.h"
# include <unistd.h>
#include <math.h>
# include <stdio.h>
# include "cub3d.h"
# include "get_next_line.h"

 void            my_mlx_pixel_put(t_mg *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    if (x < g_data.reso_one && y < g_data.reso_two && x > 0 && y > 0)
    *(unsigned int*)dst = color;
}

int is_wall(double x, double y)
{
  if ((int)x >= MAP_HOR * TILE_SIZE || (int)x <= 0 ||
      (int)y >= MAP_VER * TILE_SIZE || (int)y <= 0)
      return (1);
      
    return(map[(int)floor(y/TILE_SIZE)][(int)floor(x / TILE_SIZE)]);
}
  void get_resolution(char **content, int ab)
  {
    int i;
    int a;
    int b;
    char *r_one;
    char *r_two;
    i = 2;
    a = 0;
    while (content[ab][i++] != ' ')
      a++;
    r_one = ft_substr(content[0],2,a);
    a = 0;
    b = i;
    while(content[0][i++] != '\0')
        a++;
    r_two = ft_substr(content[0],b,a);
    g_data.reso_one = ft_atoi(r_one);
    g_data.reso_two = ft_atoi(r_two);
    free(r_one);
    free(r_two);
  }

  char **get_line()
  {
    char *line;
    char **content;
    int fd;
    int i;
    i = 0;
    fd = open("map.cub",O_RDONLY);
    content = malloc(30 * sizeof(char *));

    while (get_next_line(fd,&line))
    {
      if (*line == 0)
        free(line);
      else if (line != '\0')
        content[i++] = line;
      else
      {
        perror("Error:");
        exit(1);
      }
    }
    content[i] = NULL;
    return (content);
  }
  char *get_texture(char **content, int ab)
  {
    int i;
    int a;
    char *text;

    a = 0;
    if (content[ab][0] == 'S')
    i = 2;
    else
    i = 3;
    while (content[ab][a] != '\0')
    a++;
    text = ft_substr(content[ab],i,a);

   return(text);
  }
  void removespace(char **content, int ab, int ia)
  {
    int i;
    int a;

    i = 0;
    a = 0;
    while (content[ab][i] != '\0')
    {
      if (content[ab][i] != ' ')
      {
      g_data.map[ia][a] = content[ab][i];
      a++;
      }
      i++;
    }
  }
  int getarray(char **content, int ab, int aa)
  {
    int hor;
    int ver;
    int i;

    i = 0;
    hor = 0;
    ver = ab;
    if (aa == 1)
    return (1);
    while (content[ver] != NULL)
      ver++;
    while (content[ab][hor] != '\0')
      hor++;
    ver = ver - ab;
    g_data.ver = ver;
    g_data.map = malloc((ver + 1) * sizeof(char *));
    g_data.map[ver] = NULL;
    hor = hor/2 + 1;
    g_data.hor = hor;
    while (i < ver)
    {
     g_data.map[i++] = calloc(hor + 1,sizeof(char));
    }
    //removespace(content, ab, ia);
    return (1);
  }

  void get_settings()
  {
    char **content;
    int ab;
    int aa;
    int ia;
    
    ia = 0;
    aa = 0;
    ab = 0;

      content = get_line();
      while (content[ab] != NULL)
      {
        if (content[ab][0] == 'R')
        get_resolution(content, ab);
        else if (content[ab][0] == 'N' && content[ab][1] == 'O')
          g_data.NO = get_texture(content, ab);
        else if (content[ab][0] == 'S' && content[ab][1] == 'O')
          g_data.SO = get_texture(content, ab);
        else if (content[ab][0] == 'W' && content[ab][1] == 'E')
          g_data.WE = get_texture(content, ab);
        else if (content[ab][0] == 'E' && content[ab][1] == 'A')
          g_data.EA = get_texture(content, ab);
        else if (content[ab][0] == 'S')
          g_data.S = get_texture(content, ab);  
        else if (content[ab][0] == '1')
        {
         aa = getarray(content, ab, aa);
          removespace(content, ab, ia);         
         
         ia++;
        }

       /*else if (content[ab][0] == 'F')
        else if (content[ab][0] == 'C')*/
        ab++;
      }
  }

void playerSettings()
{
  g_player.x = g_data.reso_one / 2;
  g_player.y = g_data.reso_two / 2;
  g_player.radius = 3;
  g_player.turnDirection = 0;
  g_player.walkDirection = 0;
  g_player.rotationAngle = 90.0;
  g_player.moveSpeed = 10;
  g_player.rotationSpeed = 5.0;
}


void find_int(float interx,float intery)
{
  printf("%f\n",interx / TILE_SIZE);
  printf("%f\n",intery / TILE_SIZE);
}

void draw_player()
{
  int i;
  i = 1;
  float fakey;
  float fakex;

    //float x = g_player.rotationAngle;

    fakex = g_player.x + cos(g_player.rotationAngle * (M_PI/180));
    fakey = g_player.y + sin(g_player.rotationAngle * (M_PI/180));


     int ang = 1;
   while (ang < 360)
   {
       //mlx_pixel_put(g_mlx.mlx_ptr,g_mlx.win_ptr, circle_size * cos(ang * PI / 180) + g_player.x, circle_size * sin(ang * PI / 180) + g_player.y, RED);
        my_mlx_pixel_put(&g_mg, circle_size * cos(ang * PI / 180) + g_player.x, circle_size * sin(ang * PI / 180) + g_player.y, RED);

       ang++;
   }
     float x = g_player.rotationAngle - 30;
     float fov = 60;
    while(fov >= 0)
    {
      while (i < 500)
      {
        if (is_wall(g_player.x + cos(x * PI / 180) * i,g_player.y + sin (x * PI / 180) * i) == 1)
        {
          break;
        }
        else
        my_mlx_pixel_put(&g_mg, g_player.x + cos(x * PI / 180) * i, g_player.y + sin (x * PI / 180) * i, GOLD);
        i++;
      }
        //find_int(g_player.x + cos(x * PI / 180) * i, g_player.y + sin (x * PI / 180) * i);
        x+= (60.0 / g_data.reso_one);
       i = 0;
       fov = fov - (60.0 / g_data.reso_one);
     }
}



void sqr(int Y, int X, int color)
{ 
    int x = X;
    int y = Y;
    int lenx = 0;
    int leny = 0;
    while (lenx < TILE_SIZE)
    {
      while (leny < TILE_SIZE)
      {
        //mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, x, y, color);
        my_mlx_pixel_put(&g_mg,x,y,color);
        leny++;
        y++;
      }
      leny = 0;
      y = Y;
      lenx++;
      x++;
    }
}
void draw()
{

  int i;
  int j;
  int tile_i;
  int tile_j;
  j = 0;
  i = 0;

   while (i < 23)
   {  
    while (j < 27)
    {
      tile_i = i * TILE_SIZE;
      tile_j = j * TILE_SIZE;
        if (map[i][j] == 1)       
          sqr(tile_i,tile_j,WHITE);
        j++;
    }
   j = 0;
   i++;
 }

}

int keyPress(int key)
{

if (key == 126) //UP
      g_player.walkDirection = 1;

if (key == 125) //D
      g_player.walkDirection = -1;

if (key == 123) //L
      g_player.turnDirection = -1;

if (key == 124) //R
      g_player.turnDirection = 1;

if (key == 53)
      {
        mlx_destroy_window(g_mlx.mlx_ptr,g_mlx.win_ptr);
        exit(1);
      }
  
      return (0);
}

int keyRelease(int key)
{
  if (key == 126) //UP
      g_player.walkDirection = 0;

    if (key == 125) //D
      g_player.walkDirection = 0;

    if (key == 123) //L
      g_player.turnDirection = 0;

    if (key == 124) //R
      g_player.turnDirection = 0;
      return (0);
}
int g_Trays[25] = {0};



void CastAllRays()
{
  int columnId;
  int rayAngle;
  int i;

  rayAngle =  g_player.rotationAngle - (FOV_ANGLE / 2);
  columnId = 0;
  i = 0;
  while (i <  NUM_RAYS)
  {
    //RayR(rayAngle);

    rayAngle += FOV_ANGLE / NUM_RAYS;
    columnId++;
    i++;
  }
}

 int update()
  {
    double fakex;
    double fakey;

    mlx_hook(g_mlx.win_ptr,2,0,keyPress,0);
    mlx_hook(g_mlx.win_ptr,3,0,keyRelease,0);
    mlx_clear_window(g_mlx.mlx_ptr,g_mlx.win_ptr);

    g_player.rotationAngle += g_player.turnDirection * g_player.rotationSpeed ;//* (M_PI/180);
    //g_player.rotationAngle = fmod(g_player.rotationAngle,360); // Unable to exceed 360 on RotationAngle
    g_player.moveStep = g_player.walkDirection * g_player.moveSpeed;
    fakex = g_player.x + cos(g_player.rotationAngle * (M_PI/180)) * g_player.moveStep;
    fakey = g_player.y + sin(g_player.rotationAngle * (M_PI/180)) * g_player.moveStep;
    //printf("%d\n", is_wall(fakex, fakey));
    //printf("%f\n",g_player.rotationAngle);
    if (is_wall(fakex, fakey) != 1)
    {
      g_player.x = fakex;
      g_player.y = fakey;
    }
    draw();
    draw_player();
    //CastAllRays();

    // I should Implement two Functions for First and Last Intersection after sending rays.

    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
    mlx_destroy_image(g_mlx.mlx_ptr,g_mg.img);
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);

   //mlx_pixel_put(g_mlx.win_ptr,g_mlx.win_ptr,0,0,AQUA);
  	//printf("%d\n",g_player.walkDirection);
    // printf("%f\n",g_player.rotationAngle);
  return(0);
  }
  int main()
  {
  get_settings();
  playerSettings();
  g_mlx.mlx_ptr = mlx_init();
  g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr,g_data.reso_one,g_data.reso_two,"Maro");
  g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
  g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);


  //draw();
  //draw_player();
 //Put everything on deal_key
	mlx_loop_hook(g_mlx.mlx_ptr,update,(void *)0);
	mlx_loop(g_mlx.mlx_ptr);
return(0);
}