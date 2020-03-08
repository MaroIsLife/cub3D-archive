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

void sqr(int Y, int X, int color)
{ 
    int x = X;
    int y = Y;
    int lenx = 0;
    int leny = 0;
    int tile;

    tile = TILE_SIZE;
    while (lenx < tile)
    {
      while (leny < tile)
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
    angle = remainder(angle,(2 * M_PI));
    if (angle < 0)
    {
      angle = (2 * M_PI) + angle;
    }
    return (angle);
  }

float	normalizeangle2(float rayangle)
{
	rayangle = remainderf(rayangle,  360);
	if (rayangle < 0)
		rayangle = 360 + rayangle;
	return(rayangle);
}

void playerSettings()
{
  g_player.x = g_data.reso_one / 2;
  g_player.y = g_data.reso_two / 2;
  g_player.radius = 3;
  g_player.turnDirection = 0;
  g_player.walkDirection = 0;
  g_player.rotationAngle = 90;
  g_player.moveSpeed = 10;
  g_player.rotationSpeed = 5.0;
}

void raySettings()
{
        // g_ray.wallhitX = 0;
        // g_ray.wallhitY = 0;
        // g_ray.distance = 0;
        // g_ray.wasHitVertical = 0;
        // g_ray.isRayFacingDown = g_ray.rayAngle > 0 && g_ray.rayAngle < M_PI;
        // g_ray.isRayFacingUp = !g_ray.isRayFacingDown;
        // g_ray.isRayFacingRight = g_ray.rayAngle < 0.5 * M_PI || g_ray.rayAngle > 1.5 * M_PI;
        // g_ray.isRayFacingLeft = !g_ray.isRayFacingRight;

        // if (g_ray.rayAngle >= 0 && g_ray.rayAngle <= 180)
		    // g_ray.isRayFacingDown = 1;
	      // if (g_ray.isRayFacingRight <= 90 || g_ray.isRayFacingRight >= 270)
		    // g_ray.isRayFacingRight = 1;
	      // g_ray.isRayFacingUp = !g_ray.isRayFacingDown;
	      // g_ray.isRayFacingLeft = !g_ray.isRayFacingRight;
        
}

float distanceBetweenPoints(float wallhitX, float wallhitY)
{
  return(sqrt((wallhitX - g_player.x) * (wallhitX - g_player.x) + (wallhitY - g_player.y) * (wallhitY - g_player.y)));
}


void cast(float rayAngle,int id)
{
  float xintercept;
  float yintercept;
  float xstep;
  float ystep;
  int foundHorzWallHit = 0;
  float horzWallhitx = 0;
  float horzWallhity = 0;
  //int horzWallContent = 0;
  int isRayFacingDown = 0;
  int isRayFacingUp = 0;
  int isRayFacingRight = 0;
  int isRayFacingLeft;
  int nextHorzTouchX;
  int nextHorzTouchY;
  float xtocheck;
  float ytocheck;

  rayAngle = normalizeAngle(rayAngle);


   if (rayAngle >= 0 && rayAngle <= 180)
		    isRayFacingDown = 1;
	  if (isRayFacingRight <= 90 || isRayFacingRight >= 270)
		    isRayFacingRight = 1;
	      isRayFacingUp = !isRayFacingDown;
	      isRayFacingLeft = !isRayFacingRight;

    //HORIZONTAL PART
  yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
  yintercept += isRayFacingDown ? TILE_SIZE : 0;

  xintercept = g_player.x + (yintercept - g_player.y) / tan(rayAngle * (M_PI / 180));
  ystep = TILE_SIZE;
  ystep *= isRayFacingUp ? -1 : 1;

  xstep = TILE_SIZE / tan(rayAngle * (M_PI / 180));
  xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
  xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

  nextHorzTouchX = xintercept;
  nextHorzTouchY = yintercept;

  while (nextHorzTouchX >= 0 && nextHorzTouchX <= g_data.reso_one && nextHorzTouchY >= 0 && nextHorzTouchY <= g_data.reso_one)
  {
    xtocheck = nextHorzTouchX;
    ytocheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
    if (is_wall(xtocheck,ytocheck))
    {
        horzWallhitx = nextHorzTouchX;
        horzWallhity = nextHorzTouchY;
        //horzWallContent = map[(int)floor(ytocheck / TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
        foundHorzWallHit = 1;
        break;
    }
    else
    {
        nextHorzTouchX += xstep;
        nextHorzTouchY += ystep;
    }
  }

  //VERTICAL PART
  int foundVerWallHit = 0;
  int verWallhitx = 0;
  int verWallhity = 0;
  //int verWallContent = 0;
  int nextVerTouchX;
  int nextVerTouchY;


    xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

  yintercept = g_player.y + (xintercept - g_player.x) * tan(rayAngle * (M_PI / 180));
  xstep = TILE_SIZE;
  xstep *= isRayFacingLeft ? -1 : 1;

  ystep = TILE_SIZE * tan(rayAngle * (M_PI / 180));
  ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
  ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

  nextVerTouchX = xintercept;
  nextVerTouchY = yintercept;

  while (nextVerTouchX >= 0 && nextVerTouchX <= g_data.reso_one && nextVerTouchY >= 0 && nextVerTouchY <= g_data.reso_one)
  {
    xtocheck = nextVerTouchX + (isRayFacingLeft ? -1 : 0);
    ytocheck = nextVerTouchY;
    if (is_wall(xtocheck,ytocheck))
    {
        verWallhitx = nextVerTouchX;
        verWallhity = nextVerTouchY;
        //verWallContent = map[(int)floor(ytocheck / TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
        foundVerWallHit = 1;
        break;
    }
    else
    {
        nextVerTouchX += xstep;
        nextVerTouchY += ystep;
    }
  }

  //Calculate Distances and choosing the smallest one
  float horzHitDistance;
  float verHitDistance;

  horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(horzWallhitx,horzWallhity) : INT_MAX;
  verHitDistance = foundVerWallHit ? distanceBetweenPoints(verWallhitx,verWallhity) : INT_MAX;

  if (verHitDistance < horzHitDistance)
  {
      g_ray[id].distance = verHitDistance;
      g_ray[id].wallhitX = verWallhitx;
      g_ray[id].wallhitY = verWallhity;
      g_ray[id].wasHitVertical = 1;
     // g_ray[id].wallHitContent = verWallContent;
  }
  else
  {
     g_ray[id].distance = horzHitDistance;
      g_ray[id].wallhitX = horzWallhitx;
      g_ray[id].wallhitY = horzWallhity;
      g_ray[id].wasHitVertical = 0;
      //g_ray[id].wallHitContent = horzWallContent;
  }
  
  g_ray[id].rayAngle = rayAngle;
  g_ray[id].isRayFacingDown = isRayFacingDown;
  g_ray[id].isRayFacingUp = isRayFacingUp;
  g_ray[id].isRayFacingLeft = isRayFacingLeft;
  g_ray[id].isRayFacingRight = isRayFacingRight;

}

void render3DProjectedWalls()
{
  int i;
  float wallStripHeight;
  float rayDistance;
  float distanceProjectionPlane;
  int ybegin;

  i = 0;

  while (i  < NUM_RAYS)
  {
    rayDistance = g_ray[i].distance;
    //Calculate Distance to projection plane
    distanceProjectionPlane = (g_data.reso_one / 2) / tan(FOV_ANGLE / 2);
    wallStripHeight = (TILE_SIZE / rayDistance) * distanceProjectionPlane;
    ybegin = (g_data.reso_one / 2) - (wallStripHeight / 2);
    while (ybegin < g_data.reso_one && ybegin >= 0)
    {
      my_mlx_pixel_put(&g_mg,i,ybegin,WHITE);
      ybegin++;
    }

  }

}

void draw_player()
{
  // int i;
  // i = 1;
  float fakey;
  float fakex;
  float rayAngle;

    // float x = g_player.rotationAngle;

    fakex = g_player.x + cos(g_player.rotationAngle * (M_PI/180));
    fakey = g_player.y + sin(g_player.rotationAngle * (M_PI/180));


     int ang = 1;
   while (ang < 360)
   {
        my_mlx_pixel_put(&g_mg, circle_size * cos(ang * PI / 180) + g_player.x , circle_size * sin(ang * PI / 180) + g_player.y , RED);
       ang++;
   }
    rayAngle = g_player.rotationAngle; //- 30;
    //  float fov = 60;
     int    i;
    
    // while(fov >= 0)
    // {
      i = 0;
      while (i < 100)
      {
        // my_mlx_pixel_put(&g_mg, g_player.x + cos(rayAngle * PI / 180) * i, g_player.y + sin(rayAngle * PI / 180) * i, GOLD);
         my_mlx_pixel_put(&g_mg, g_player.x + cos(rayAngle * PI / 180) * i, g_player.y + sin(rayAngle * PI / 180) * i, GOLD);       
        i++;
      } 
    //     g_ray[0].rayAngle+= (60.0 / g_data.reso_one);
    //     fov = fov - (60.0 / g_data.reso_one);
    //  }
     //printf("%f\n",g_ray.rayAngle);
}



void CastAllRays()
{
  int id;
  float rayAngle;

  id = 0;
  rayAngle = g_player.rotationAngle - (FOV_ANGLE / 2);
  while (id < NUM_RAYS)
  {
    cast(rayAngle,id);
    rayAngle +=  60 / (float)NUM_RAYS;
    id++;
  } 
  id = 0;
  render3DProjectedWalls();
}

// void cast2(int id,float rayAngle)
// {
//   float xintercept;
//   float yintercept;
//   float xstep;
//   float ystep;
//   float foundHorzWallHit;
//   float horzWallhitX;
//   float horzWallHitY;
//   float horzWallColor;

//   foundHorzWallHit = 0;
//   horzWallhitX = 0;
//   horzWallHitY = 0;
//   horzWallColor = 0;

//   yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
//   yintercept += g_ray[id].isRayFacingDown ? TILE_SIZE : 0;

//   xintercept = g_player.x + (yintercept - g_player.y) / tan(rayAngle)

// }

// void CastAllRays2()
// {
//   int id;
//   float rayAngle;

//   id = 0;
//   rayAngle = g_player.rotationAngle - (FOV_ANGLE / 2);
//   //g_ray[0].rayAngle =g_player.rotationAngle - (FOV_ANGLE / 2);
//   while (id < NUM_RAYS)
//   {
//     cast(id);
//      rayAngle +=  FOV_ANGLE / NUM_RAYS;
//     id++;
//   } 
   //draw()
//}

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

void renderRays()
{
  int i;

  i = 0;
  while (i <  NUM_RAYS)
  {

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
    //draw();
    //draw_player();
    // printf("%f\n",g_player.rotationAngle);
    // draw();
    // draw_player();
    CastAllRays();
    // render3DProjectedWalls();
    

  
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
    mlx_destroy_image(g_mlx.mlx_ptr,g_mg.img);
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
  return(0);
  }

  // void render3DProjectedWalls()
  // {
  //   int i;
  //   int ray;

  //   i = 0;
  //   while (i < NUM_RAYS)
  //   {

  //     ray = rays[i];

  //     i++;
  //   }

  // }
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
