# include "cub3d.h"

 void            my_mlx_pixel_put(t_mg *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    if (x < g_data.reso_one && y < g_data.reso_two && x > 0 && y > 0)
    *(unsigned int*)dst = color;
}

int     get_rgb(int r, int g, int b)
{
    return (b + g * 256 + r * 65536);
}

int get_color(char **content, int ab)
{
  int i;
  int a;
  int b;
  char *s;

  i = 0;
  a = 0;
  while (content[ab][a] < 48 || content[ab][a] > 57)
    a++;

  b = a;
  while (content[ab][a] != ',')
  {
    i++;
    a++;
  }

   s = ft_substr(content[ab],b,i);
   g_color.r = ft_atoi(s);

  b = a + 1;
  a++;
  i = 0;
  while (content[ab][a] != ',')
  {
    i++;
    a++;
  }
  s = ft_substr(content[ab],b,i);
  g_color.g = ft_atoi(s);
  b = a + 1;
  a++;
  i = 0;
  while (content[ab][a] != '\0')
  {
    i++;
    a++;
  }
  s = ft_substr(content[ab],b,i);
  g_color.b = ft_atoi(s);

  if (g_color.b < 0 || g_color.g < 0 || g_color.r < 0)
  {
    perror("Negative number");
    exit (-1);
  }

    return (g_color.b + g_color.g * 256 + g_color.r * 65536);
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

void check_map()
{

  int i;
  int j;
  double tile_i;
  double tile_j;
  j = 0;
  i = 0;

   while (i < g_data.ver) // < ver
   {  
    while (j < g_data.hor) // < hor
    {
      tile_i = ((double)i + 0.5) * TILE_SIZE;
      tile_j = ((double)j + 0.5) * TILE_SIZE;
       if (g_data.map[i][j] == 'N' | g_data.map[i][j] == 'W' || g_data.map[i][j] == 'S' || g_data.map[i][j] == 'E')
       {
         if (g_player.found == 1)
         {
           perror("Duplicate Players");
           exit (1);
         }
         g_player.found = 1;
          if (g_data.map[i][j] == 'N')
            g_player.rotationAngle = 270;
          else if (g_data.map[i][j] == 'W')
            g_player.rotationAngle = 180;
          else if (g_data.map[i][j] == 'S')
            g_player.rotationAngle = 90;
          else if (g_data.map[i][j] == 'E')
            g_player.rotationAngle = 0;

          g_player.x = tile_j;
          g_player.y = tile_i;
         g_data.map[i][j] = '0';
        }
        j++;
    }
   j = 0;
   i++;
  }
     if(g_player.found == 0)
 {
  perror("No Player found");
  exit(1);
 }
}



int is_wall(double x, double y)
{
  if ((int)x >= g_data.hor * TILE_SIZE || (int)x <= 0 || //Hor
      (int)y >= g_data.ver * TILE_SIZE || (int)y <= 0) // Ver
      return (1);
      
    return(g_data.map[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] - '0');
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
    fd = open(g_data.mapName,O_RDONLY);
    if (fd == -1)
    {
      perror("The Map could not be found.");
      exit(-1);
    }
    content = malloc(80 * sizeof(char *));

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
    content[i] = line;
    i++;
    content[i] = NULL;
    return (content);
  }
  char *get_texture(char **content, int ab)
  {
    int i;
    int a;
    char *text;

    a = 0;
    if (content[ab][0] == 'S' && content[ab][1] == ' ')
    i = 2;
    else
    i = 3;
  
    while (content[ab][a] != '\0')
    a++;
    text = ft_substr(content[ab],i,a);
     i = ft_strlen(text);
     if (i == 2 || i == 3)
     {
       perror("Missing Texture");
       exit (1);
     }

   return(text);
  }
  
  int getarray(char **content, int ab, int aa)
  {
    int hor;
    int ver;
    int i;
    int fhor;

    if (aa == 1)
    return (1);
    g_data.mapstart = ab;
    i = 0;
    hor = 0;
    ver = ab;
    while (content[ver] != NULL)
      ver++;
    ver = ver - ab;
    g_data.ver = ver;
    g_data.map = malloc((ver + 1)  * sizeof(char *));
    g_data.map[ver] = NULL;
    fhor = ab;
    while (content[fhor] != NULL)
    {
      while (content[fhor][i] != '\0')
        i++;
      if (i > g_data.hor)
        g_data.hor = i;

        i = 0;
        fhor++;
    }
    i = 0;
    while (i < ver)
    {
     g_data.map[i++] = calloc((g_data.hor + 1),sizeof(char));
    }
    return (1);
  }
  
  
  void int_map(char **content)
      {
      int a;
      int i;
      int b;

      a = g_data.mapstart;
      b = 0;
      i = 0;
      while (content[a] != NULL)
      {
        while (content[a][i] != '\0')
        {
          g_data.map[b][i] = content[a][i];
          i++;
        }
        a++;
        b++;
        i = 0;
      }
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
          else if (content[ab][0] == 'F')
          g_data.Fcolor = get_color(content,ab);
          else if (content[ab][0] == 'C')
          g_data.Ccolor = get_color(content,ab);
        else if (content[ab][0] == '1' || content[ab][0] == ' ')
        {
         aa = getarray(content, ab, aa);
         ia++;
        }
        ab++;
      }
      int_map(content);

      // int abs = 0;
      // while (g_data.map[abs] != NULL)
      // {
      //   printf("%s\n",g_data.map[abs]);
      //   abs++;
      // }


  }

  float normalizeAngle(float angle)
  {
    angle = remainder(angle,(360));
    if (angle < 0)
    {
      angle = (360) + angle;
    }
    return (angle);
  }



void playerSettings()
{
  // g_player.x = g_data.reso_one / 2;
  // g_player.y = g_data.reso_two / 2;
  g_player.radius = 3;
  g_player.turnDirection = 0;
  g_player.walkDirection = 0;
  //g_player.rotationAngle = 360; // Moved to check_map()
  g_player.moveSpeed = 8;
  g_player.rotationSpeed = 3;
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
  float nextHorzTouchX;
  float nextHorzTouchY;
  float xtocheck;
  float ytocheck;

  rayAngle = normalizeAngle(rayAngle);


   if (rayAngle >= 0 && rayAngle <= 180)
		    isRayFacingDown = 1;
	  if (rayAngle <= 90 || rayAngle >= 270)
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

  while (nextHorzTouchX >= 0 && nextHorzTouchX <= g_data.reso_one * TILE_SIZE && nextHorzTouchY >= 0 && nextHorzTouchY <= g_data.reso_two * TILE_SIZE) // reso one
  {
    xtocheck = nextHorzTouchX;
    ytocheck = nextHorzTouchY + (isRayFacingUp ? - 1 : 0);
    if (is_wall(xtocheck,ytocheck))
    {
        horzWallhitx = nextHorzTouchX;
        horzWallhity = nextHorzTouchY;
        //horzWallContent = map[(int)floor(ytocheck / TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
        foundHorzWallHit = 1;
        break ;
    }
        nextHorzTouchX += xstep;
        nextHorzTouchY += ystep;
  }

  //VERTICAL PART
  int foundVerWallHit = 0;
  float verWallhitx = 0;
  float verWallhity = 0;
  //int verWallContent = 0;
  float nextVerTouchX;
  float nextVerTouchY;


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

  while (nextVerTouchX >= 0 && nextVerTouchX <= g_data.reso_one * TILE_SIZE && nextVerTouchY >= 0 && nextVerTouchY <= g_data.reso_one * TILE_SIZE) // reso _one
  {
    xtocheck = nextVerTouchX + (isRayFacingLeft ? -1 : 0);
    ytocheck = nextVerTouchY;
    if (is_wall(xtocheck,ytocheck))
    {
        verWallhitx = nextVerTouchX;
        verWallhity = nextVerTouchY;
        //verWallContent = map[(int)floor(ytocheck / TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
        foundVerWallHit = 1;
        break ;
    }
        nextVerTouchX += xstep;
        nextVerTouchY += ystep;
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
      g_ray[id].offset = (int)verWallhity % TILE_SIZE;
      g_ray[id].wasHitVertical = 1;
     // g_ray[id].wallHitContent = verWallContent;
  }
  else
  {
     g_ray[id].distance = horzHitDistance;
      g_ray[id].wallhitX = horzWallhitx;
      g_ray[id].wallhitY = horzWallhity;
      g_ray[id].offset = (int)horzWallhitx % TILE_SIZE;
      g_ray[id].wasHitVertical = 0;
      //g_ray[id].wallHitContent = horzWallContent;
  }
  
  g_ray[id].rayAngle = rayAngle;
  g_ray[id].isRayFacingDown = isRayFacingDown;
  g_ray[id].isRayFacingUp = isRayFacingUp;
  g_ray[id].isRayFacingLeft = isRayFacingLeft;
  g_ray[id].isRayFacingRight = isRayFacingRight;
}

// void draw_player()
// {
//   // int i;
//   // i = 1;
//   float fakey;
//   float fakex;
//   float rayAngle;

//     // float x = g_player.rotationAngle;

//     fakex = g_player.x + cos(g_player.rotationAngle * (M_PI/180));
//     fakey = g_player.y + sin(g_player.rotationAngle * (M_PI/180));


//      int ang = 1;
//    while (ang < 360)
//    {
//         my_mlx_pixel_put(&g_mg, circle_size * cos(ang * PI / 180) + g_player.x , circle_size * sin(ang * PI / 180) + g_player.y , RED);
//        ang++;
//    }
//     rayAngle = g_player.rotationAngle; //- 30;
//     //  float fov = 60;
//      int    i;
    
//     // while(fov >= 0)
//     // {
//       i = 0;
//       while (i < 100)
//       {
//         // my_mlx_pixel_put(&g_mg, g_player.x + cos(rayAngle * PI / 180) * i, g_player.y + sin(rayAngle * PI / 180) * i, GOLD);
//          my_mlx_pixel_put(&g_mg, g_player.x + cos(rayAngle * PI / 180) * i, g_player.y + sin(rayAngle * PI / 180) * i, GOLD);       
//         i++;
//       } 
//     //     g_ray[0].rayAngle+= (60.0 / g_data.reso_one);
//     //     fov = fov - (60.0 / g_data.reso_one);
//     //  }
//      //printf("%f\n",g_ray.rayAngle);
// }

void init_texture()
{
  int i;

  i = 0;


    open_txt(g_data.SO);
    open_txt(g_data.NO);
    open_txt(g_data.WE);
    open_txt(g_data.EA);

  g_txt.ptr[0] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.WE,&g_txt.width[0],&g_txt.height[0]);
  g_txt.data[0] = (int *)mlx_get_data_addr(g_txt.ptr[0],&g_txt.bpp,&g_txt.line,&g_txt.endian);

  g_txt.ptr[1] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.EA,&g_txt.width[1],&g_txt.height[1]);
  g_txt.data[1] = (int *)mlx_get_data_addr(g_txt.ptr[1],&g_txt.bpp,&g_txt.line,&g_txt.endian);

  g_txt.ptr[2] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.NO,&g_txt.width[2],&g_txt.height[2]);
  g_txt.data[2] = (int *)mlx_get_data_addr(g_txt.ptr[2],&g_txt.bpp,&g_txt.line,&g_txt.endian);

  g_txt.ptr[3] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.SO,&g_txt.width[3],&g_txt.height[3]);
  g_txt.data[3] = (int *)mlx_get_data_addr(g_txt.ptr[3],&g_txt.bpp,&g_txt.line,&g_txt.endian);
}

void	wall_data(int id)
{
  int top;

	float distance = g_ray[id].distance * cos((g_ray[id].rayAngle - g_player.rotationAngle) * (M_PI / 180));
	float projection = (g_data.reso_one / 2) / tan((60/2) * (M_PI / 180));
	float wallheight = (TILE_SIZE / distance) * projection;

	top = (g_data.reso_two / 2) - ((int)wallheight / 2);
  // if (top< 0)
  //   top = 0;
  
	int	bottom = top + wallheight;
	g_ray[id].top = top;
	g_ray[id].bottom = bottom;
	g_ray[id].height = wallheight;
}
void	draw_floor(int id)
{
	
	int i = 0;

	while (i < g_ray[id].top)
	{
		my_mlx_pixel_put(&g_mg, id, i, g_data.Ccolor);
		i++;
	}
	i = g_ray[id].bottom;
	while (i < g_data.reso_two)
	{
		my_mlx_pixel_put(&g_mg, id, i, g_data.Fcolor);
		i++;
	}
}
void	draw_wall(int id, int nb)
{
	float a;
	float b;
  int o;
    float f;
    float i;

  o = 0;
  i = 0.;
  a = g_ray[id].top;
  b = g_ray[id].bottom;


  f = (float)g_txt.height[nb] / g_ray[id].height;

	b > g_data.reso_two ? b = g_data.reso_two : 0;
	while (a < b)
	{
      if ((int)i * g_txt.width[nb] + (int)g_ray[id].offset < g_txt.width[nb] * g_txt.height[nb]
			&& id >= 0 && id < g_data.reso_one && id < g_data.reso_two && g_txt.width[nb] < g_data.reso_one)
		{
			my_mlx_pixel_put(&g_mg, id, a, g_txt.data[nb][(int)(i) * g_txt.width[nb] + (int)g_ray[id].offset]);
		}	
	  a++;
    i+= f;
	}
}
int		direction(int nb, int id)
{
	if (g_ray[id].wasHitVertical == 1)
	{
		if (g_ray[id].isRayFacingLeft == 1)
			nb = 0;
		if (g_ray[id].isRayFacingRight == 1)
			nb = 1;
	}
	if (g_ray[id].wasHitVertical == 0)
	{
		if (g_ray[id].isRayFacingUp == 1)
			nb = 2;
		if (g_ray[id].isRayFacingDown == 1)
			nb = 3;
	}
	return (nb);
}

void CastAllRays()
{
  int id;
  float rayAngle;
  int nb;

  id = 0;
  rayAngle = g_player.rotationAngle - (60 / 2);
  while (id < g_data.reso_one)
  { 
    cast(rayAngle,id);
     rayAngle +=  60.0 / (float)g_data.reso_one;
    id++;
  } 
  id = 0;
  while (id < g_data.reso_one)
  {
      wall_data(id);
      id++;
  }
  init_texture();
  id = 0;
  while (id < g_data.reso_one)
  {
      nb = direction(nb,id);
      draw_floor(id);
      draw_wall(id,nb);
      id++;
  }
}

int keyPress(int key)
{

if (key == 126 || key == 13) //UP
      g_player.walkDirection = 1;

if (key == 2)
{
      g_player.directionLR = 90;
      g_player.walkDirection = 1;
}

if (key == 0)
{
  g_player.directionLR = 270;
  g_player.walkDirection = 1;
}

if (key == 125 || key == 1) 
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
  if (key == 126 || key == 13) //UP
      g_player.walkDirection = 0;

    if (key == 125 || key == 1) //D
      g_player.walkDirection = 0;

    if (key == 2)
    {
      g_player.directionLR = 0;
      g_player.walkDirection = 0;
    }

    if (key == 0)
    {
      g_player.directionLR = 0;
      g_player.walkDirection = 0;
    }

    if (key == 123) //L
      g_player.turnDirection = 0;

    if (key == 124) //R
      g_player.turnDirection = 0;
      return (0);
}

int red()
{
  exit(-1);
}

 int update()
  {
    double fakex;
    double fakey;

    mlx_hook(g_mlx.win_ptr,2,0,keyPress,0);
    mlx_hook(g_mlx.win_ptr,3,0,keyRelease,0);
    mlx_clear_window(g_mlx.mlx_ptr,g_mlx.win_ptr);

    g_player.rotationAngle += g_player.turnDirection * g_player.rotationSpeed;//* (M_PI/180);
    g_player.rotationAngle = fmod(g_player.rotationAngle,360); // Unable to exceed 360 on RotationAngle
    g_player.moveStep = g_player.walkDirection * g_player.moveSpeed;
    fakex = g_player.x + cos((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep * 5);
    fakey = g_player.y + sin((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep * 5);


    
    if (is_wall(fakex, fakey) != 1)
    {
      g_player.x += cos((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep);
      g_player.y += sin((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep);
    }
    
    CastAllRays();


    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
    mlx_destroy_image(g_mlx.mlx_ptr,g_mg.img);
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
    return(0);
  }


  void  arg_check(char *s1)
  {
    int i;
    char **s2;
    char *s3;
    int a;

    a = 0;
    i = 0;
    s3 = "cub";

    while (s1[i] != '\0')
    {
      if (s1[i] == '.')
      {
        s2 = ft_split(s1,'.');           
        a = 1;
      }
      i++;
    }
    if (a == 0)
    {
      perror("Please insert the correct map that ends with .cub");
      exit(1);
    }
    i = 0;
    while (s2[1][i] != '\0')
    {
      if (s2[1][i] != s3[i])
      {
        perror("Please Insert the correct map using .cub");
        exit(1);
      }
      i++;
     }
    g_data.mapName = s1;
  }


  int main(int argc, char **argv)
  {
      
  if (argc == 2 || argc == 3)
  {
    arg_check(argv[1]);
    get_settings();
    playerSettings();
    g_mlx.mlx_ptr = mlx_init();
    g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr,g_data.reso_one,g_data.reso_two,"Maro");
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
  
    all_errors();

    check_map();
	  mlx_loop_hook(g_mlx.mlx_ptr,update,(void *)0);
    mlx_hook(g_mlx.win_ptr, 17, 0,red, (void *)0);
	  mlx_loop(g_mlx.mlx_ptr);
  }
  else {
    perror("Please insert the map's name.");
  }
  return(0);
}