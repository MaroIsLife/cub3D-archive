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

  float normalizeAngle(float angle)
  {
    angle = fmod(angle,(2 * M_PI));
    if (angle < 0)
    {
      angle = (2 * M_PI) + angle;
    }
    return (angle);
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

void raySettings()
{
        g_ray.wallhitX = 0;
        g_ray.wallhitY = 0;
        g_ray.distance = 0;
        g_ray.isRayFacingDown = g_ray.rayAngle > 0 && g_ray.rayAngle < M_PI;
        g_ray.isRayFacingUp = !g_ray.isRayFacingDown;
        g_ray.wasHitVertical = 0;
        g_ray.isRayFacingRight = g_ray.rayAngle < 0.5 * M_PI || g_ray.rayAngle > 1.5 * M_PI;
        g_ray.isRayFacingLeft = !g_ray.isRayFacingRight;
        
}

float distanceBetweenPoints(int wallhitX, int wallhitY)
{
  return(sqrt((wallhitX - g_player.x) * (wallhitX - g_player.x) + (wallhitY - g_player.y) * (wallhitY - g_player.y)));

  
}

void cast(float rayAngle)
{
  float xstep;
  float ystep;
  float xintercept;
  float yintercept;
  float nextHorzTouchX;
  float nextHorzTouchY;
  float foundH;

  float hwallhitX = 0;
  float hwallhitY = 0;

  //Horizontal
  rayAngle = normalizeAngle(rayAngle);
  //find y coordinate of the closest horizontal grid
  yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
  if (g_ray.isRayFacingDown)
  {
    yintercept += TILE_SIZE;
  }
  
  
  //find x coordinate of closest horizontal grid
  xintercept = g_player.x + (yintercept - g_player.y) / tan(rayAngle * (M_PI / 180));

  //Calculate  the increment for xstep and ystep
  ystep = TILE_SIZE;

  if (g_ray.isRayFacingUp)
    ystep *= -1;

  xstep = TILE_SIZE / tan(rayAngle * (M_PI / 180));
  if(g_ray.isRayFacingLeft && xstep > 0)
  xstep *= -1;
  if (g_ray.isRayFacingRight && xstep < 0)
  xstep *= -1;

  nextHorzTouchX = xintercept;
  nextHorzTouchY = yintercept;

  if(g_ray.isRayFacingUp)
  nextHorzTouchY--;

  //Increment xstep and ystep until we find a wall

  foundH = 0;
  while (nextHorzTouchX >= 0 && nextHorzTouchX <= g_data.reso_one && nextHorzTouchY >= 0 && nextHorzTouchY <= g_data.reso_one)
  {
    if(is_wall(nextHorzTouchX,nextHorzTouchY))
    {
      foundH = 1;
      hwallhitX = nextHorzTouchX;
      hwallhitY = nextHorzTouchY;
      break;
    }
    else
    {
      nextHorzTouchX += xstep;
      nextHorzTouchY += ystep;
    }
  }

  //Vertical 
  float foundV;
  float vwallhitX;
  float vwallhitY;
  float nextVertTouchX;
  float nextVertTouchY;

  vwallhitX = 0;
  vwallhitY = 0;

  xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
  if (g_ray.isRayFacingRight)
  {
    xintercept += TILE_SIZE;
  }
  yintercept = g_player.y + (xintercept - g_player.x) * tan(rayAngle * (M_PI / 180)); // Dividing or Multiplying ??
  xstep = TILE_SIZE;

  if (g_ray.isRayFacingLeft)
    xstep *= -1;
  else
    xstep *= 1;
  

  ystep = TILE_SIZE * tan(rayAngle * (M_PI / 180));
  if(g_ray.isRayFacingUp && ystep > 0)
  ystep *= -1;
  if (g_ray.isRayFacingDown && ystep < 0)
  ystep *= -1;

  nextVertTouchX = xintercept;
  nextVertTouchY = yintercept;

  if(g_ray.isRayFacingLeft)
  nextVertTouchX--;
  foundV = 0;
  while (nextVertTouchX >= 0 && nextVertTouchX <= g_data.reso_one && nextVertTouchY >= 0 && nextVertTouchY <= g_data.reso_one)
  {
    if(is_wall(nextVertTouchX,nextVertTouchY))
    {
      foundV = 1;
      vwallhitX = nextVertTouchX;
      vwallhitY = nextVertTouchY;
      break;
    }
    else
    {
      nextVertTouchX += xstep;
      nextVertTouchY += ystep;
    }
  }

  // Calculate both distances Vertical and Horz and Choose the smallest

  float horHitDistance;
  float verHitDistance;

  if (foundH)
    horHitDistance = distanceBetweenPoints(hwallhitX,hwallhitY);
  else
  horHitDistance = INT_MAX;

  if (foundV)
    verHitDistance = distanceBetweenPoints(vwallhitX,vwallhitY);
  else
  verHitDistance = INT_MAX;

  if (horHitDistance < verHitDistance)
  {
    g_ray.wallhitX = hwallhitX;
    g_ray.wallhitY = hwallhitY;
    g_ray.distance = horHitDistance;
  }
  else
  {
    g_ray.wallhitX = vwallhitX;
    g_ray.wallhitY = vwallhitY;
    g_ray.distance = verHitDistance;
    g_ray.wasHitVertical = 1;
  }
    
  
}

void castallrays()
{
  int columnid;
  //char *raysobject;
  int i;

  i = 0;
  columnid = 0;

  //raysobject = malloc(g_data.reso_one * sizeof(char));

  while (i < NUM_RAYS)
  {

    g_ray.rayAngle += FOV_ANGLE / NUM_RAYS;
    columnid++;
    i++;
  }


}



// struct rd
// {
//   float horx;
//   float hory;
//   float horxa;
//   float horya;
// } A;

// void  f1(float dx)
// {
//   int a = dx;
//   a++;
//   if (g_player.rotationAngle > 180 && g_player.rotationAngle < 360)
//   {
//     A.hory = (int)(g_player.y / TILE_SIZE) * TILE_SIZE; //- 1;
//     A.horya = -TILE_SIZE;
//     A.horxa = -TILE_SIZE / tan(dx * (M_PI / 180)); // 60
//   }
//   else if (g_player.rotationAngle > 0 && g_player.rotationAngle < 180)
//   {
//     A.hory = (int)(g_player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
//     A.horxa = TILE_SIZE / tan(dx * (M_PI / 180)); //60
//     A.horya = TILE_SIZE;
//   }
//   A.horx = g_player.x + (g_player.y - A.hory) / tan(dx * (M_PI / 180));
//   A.horxa = TILE_SIZE / tan(dx * (M_PI / 180));
// }
// int  f2()
// {
//   while (A.hory > 0 && A.horx > 0 && A.horx < g_data.reso_one && A.hory < g_data.reso_two && map[(int)(A.hory / TILE_SIZE)][(int)(A.horx / TILE_SIZE)] != 1)
//   {
//     A.hory += A.horya;
//     A.horx += A.horxa;
//   }
//   return (sqrt(pow(A.horx - g_player.x ,2) + pow(A.hory - g_player.y,2)));
// }
// int find_distance(float dx)
// {
//   f1(dx);//first horz inter
//   return (f2());//last horz inter
//   //f3();

// }

void draw_player()
{
  int i;
  i = 1;
  float fakey;
  float fakex;

    // float x = g_player.rotationAngle;

    fakex = g_player.x + cos(g_player.rotationAngle * (M_PI/180));
    fakey = g_player.y + sin(g_player.rotationAngle * (M_PI/180));


     int ang = 1;
   while (ang < 360)
   {
        my_mlx_pixel_put(&g_mg, circle_size * cos(ang * PI / 180) + g_player.x, circle_size * sin(ang * PI / 180) + g_player.y, RED);
       ang++;
   }
     g_ray.rayAngle = g_player.rotationAngle - 30;
     float fov = 60;
    while(fov >= 0)
    {
      i = 0;//find_distance(x);
      while (i < 300)
      {
      //  if (is_wall(g_player.x + cos(x * PI / 180) * i,g_player.y + sin (x * PI / 180) * i) == 1)
      //     break;
      //   else
        my_mlx_pixel_put(&g_mg, g_player.x + cos(g_ray.rayAngle * PI / 180) * i, g_player.y + sin (g_ray.rayAngle * PI / 180) * i, GOLD);
        i++;
      } 
        g_ray.rayAngle+= (60.0 / g_data.reso_one);
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
    g_player.rotationAngle = fmod(g_player.rotationAngle,360); // Unable to exceed 360 on RotationAngle
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
    printf("%f\n",g_player.rotationAngle);
    //CastAllRays();


    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
    mlx_destroy_image(g_mlx.mlx_ptr,g_mg.img);
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
  return(0);
  }
  int main()
  {
    int a;
    int d , c;
    d = 10.;
    c = 48.;
    a = fmod(d,c);
    printf("%d\n", a);

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