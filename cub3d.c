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

// int get_color(char **content, int ab)
// {
//   int i;
//   int a;
//   int b;
//   char *s;

//   i = 0;
//   a = 0;
//   while (content[ab][a] < 48 || content[ab][a] > 57)
//     a++;

//   b = a;
//   while (content[ab][a] != ',')
//   {
//     i++;
//     a++;
//   }

//    s = ft_substr(content[ab],b,i);
//    g_color.r = ft_atoi(s);
//    free(s);

//   b = a + 1;
//   a++;
//   i = 0;
//   while (content[ab][a] != ',')
//   {
//     i++;
//     a++;
//   }
//   s = ft_substr(content[ab],b,i);
//   g_color.g = ft_atoi(s);
//   free(s);
//   b = a + 1;
//   a++;
//   i = 0;
//   while (content[ab][a] != '\0')
//   {
//     i++;
//     a++;
//   }
//   s = ft_substr(content[ab],b,i);
//   g_color.b = ft_atoi(s);
//   free(s);
//   if (g_color.b < 0 || g_color.g < 0 || g_color.r < 0)
//   {
//     perror("Negative number");
//     exit (-1);
//   }

//     return (g_color.b + g_color.g * 256 + g_color.r * 65536);
// }



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


void player_int(int i, int j)
{
  if (g_player.found == 1)
         {
           perror("Duplicate Players");
           exit (1);
         }
         if (g_data.map[i][j] == 'N')
         g_player.pos = 'N';
         else if (g_data.map[i][j] == 'W')
         g_player.pos = 'W';
         else if (g_data.map[i][j] == 'S')
         g_player.pos = 'S';
         else if (g_data.map[i][j] == 'E')
         g_player.pos = 'E';          
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
         player_int(i,j);
        
         if (g_data.map[i][j] == '2')
         g_nsprite++;
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
        else if(g_data.map[i][j] == '2')
        g_nsprite++;
        j++;
    }
   j = 0;
   i++;
  }
  if (g_player.found == 0)
 {
  perror("No Player found");
  exit(1);
 }
}




int is_wall1(float x, float y)
{
  if ((int)x >= g_data.hor * TILE_SIZE || (int)x <= 0 || //Hor
      (int)y >= g_data.ver * TILE_SIZE || (int)y <= 0 ) // Ver
      return (1);
      
    return(g_data.map[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] - '0');
}

int		is_wall(float x, float y)
{
	int mapx;
	int mapy;

	mapx = (int)floor(x / TILE_SIZE);
	mapy = (int)floor(y / TILE_SIZE);
	if (mapx >= 0 && mapy >= 0 && mapy < g_data.ver && mapx < len(g_data.map[mapy]))
	{
		if (g_data.map[mapy][mapx] != '1')
			return (1);
	}
	return (0);
}


void playerSettings()
{
  g_player.radius = 3;
  g_player.turnDirection = 0;
  g_player.walkDirection = 0;
  g_player.moveSpeed = 8;
  g_player.rotationSpeed = 3;

  if (g_data.reso_one > 2560)
    g_data.reso_one = 2560;
  if (g_data.reso_two > 1440)
    g_data.reso_two = 1440;

}
void init_texture()
{
  int i;

  i = 0;
    open_txt(g_data.SO);
    open_txt(g_data.NO);
    open_txt(g_data.WE);
    open_txt(g_data.EA);
    open_txt(g_data.S);
g_txt.ptr[0] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.WE,&g_txt.width[0],&g_txt.height[0]);
g_txt.ptr[1] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.EA,&g_txt.width[1],&g_txt.height[1]);
g_txt.ptr[2] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.NO,&g_txt.width[2],&g_txt.height[2]);
g_txt.ptr[3] = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_data.SO,&g_txt.width[3],&g_txt.height[3]);
  
if (g_txt.ptr[0] == NULL || g_txt.ptr[1] == NULL || g_txt.ptr[2] == NULL || g_txt.ptr[3] == NULL)
{
  perror("Error In texture XPM File");
  exit(1);
}
g_txt.data[0] = (int *)mlx_get_data_addr(g_txt.ptr[0],&g_txt.bpp,&g_txt.line,&g_txt.endian);
g_txt.data[1] = (int *)mlx_get_data_addr(g_txt.ptr[1],&g_txt.bpp,&g_txt.line,&g_txt.endian);
g_txt.data[2] = (int *)mlx_get_data_addr(g_txt.ptr[2],&g_txt.bpp,&g_txt.line,&g_txt.endian);
g_txt.data[3] = (int *)mlx_get_data_addr(g_txt.ptr[3],&g_txt.bpp,&g_txt.line,&g_txt.endian);
}

void	wall_data(int id)
{
  int top;

	float distance = g_ray[id].distance * cos((g_ray[id].rayAngle - g_player.rotationAngle) * (M_PI / 180));
	float projection = (g_data.reso_one / 2) / tan((60 / 2) * (M_PI / 180));
	float wallheight = (TILE_SIZE / distance) * projection;

	top = (g_data.reso_two / 2) - ((int)wallheight / 2);
  // if (top < 0)
  //   top = 0;
  
	int	bottom = top + wallheight;
	g_ray[id].top = top;
	g_ray[id].bottom = bottom;
	g_ray[id].height = wallheight;
}
void	draw_floor(int id)
{
	
	int i;

  i = 0;
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

  // printf("A: %f\n B: %f\n",a,b);
  f = (float)g_txt.height[nb] / g_ray[id].height;

	//b > g_data.reso_two ? b = g_data.reso_two : 0;
  // if (b > g_data.reso_two)
  //   b = g_data.reso_two;
  // && id >= 0 && id < g_data.reso_one && id < g_data.reso_two
	while (a < b)
	{
      if ((int)i * g_txt.width[nb] + (int)g_ray[id].offset < g_txt.width[nb] * g_txt.height[nb] && id >= 0)
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
  id = 0;
  get_sprite_pos();
	get_spriteimage();
	while (id < g_nsprite)
	{
		render_sprite(id);
		id++;
	}
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
    fakex = g_player.x + cos((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep * 8);
    fakey = g_player.y + sin((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep * 8);
    if (is_wall1(fakex, fakey) != 1 && is_wall(fakex, fakey) != 2)
    {
      g_player.x += cos((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep);
      g_player.y += sin((g_player.rotationAngle + g_player.directionLR) * (M_PI/180)) * (g_player.moveStep);
    } 
    CastAllRays();
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mg.img, 0, 0);
    if (g_player.saved == 1)
    {
      save_bitmap();
      exit(0);
    }
    mlx_destroy_image(g_mlx.mlx_ptr,g_mg.img);
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
    return(0);
  }

  int main(int argc, char **argv)
  {
 
  if (argc == 2 || argc == 3)
  {
    arg_check(argv[1]);
    if (argc == 3)
    arg_save_check(argv[2]);
    get_settings();
    playerSettings();
    g_mlx.mlx_ptr = mlx_init();
    g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr,g_data.reso_one,g_data.reso_two,"Cub3d");
    g_mg.img = mlx_new_image(g_mlx.mlx_ptr, g_data.reso_one, g_data.reso_two);
    g_mg.addr = mlx_get_data_addr(g_mg.img, &g_mg.bits_per_pixel, &g_mg.line_length,&g_mg.endian);
  
    check_map();
    all_errors();

    printf("%c\n",g_player.pos);

	  mlx_loop_hook(g_mlx.mlx_ptr,update,(void *)0);
    mlx_hook(g_mlx.win_ptr, 17, 0,red, (void *)0);
	  mlx_loop(g_mlx.mlx_ptr);
  }
  else {
    perror("Please insert the map's name.");
  }
  return(0);
}