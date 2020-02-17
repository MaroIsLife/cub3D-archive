# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include "cub3d.h"

int print_wall(int i, int j, void *mlx_ptr, void *win_ptr)
  {
  int x;
  int y;
  int X;
  int Y;
  x = j * 35;
  y = i * 35;
  X = x + 35;
  Y = y + 35;
  while(y < Y)
  {
  while(x < X)
  {
  mlx_pixel_put(mlx_ptr, win_ptr, x, y, 255);
  x++;
  }
  x = j * 35;
  y++;
  }
  return 0;
  }

  int deal_key(int key,void *param)
  {
    if (key == 53)
    {
      mlx_destroy_window(g_mlx.mlx_ptr,g_mlx.win_ptr);
      exit(1);
    }
  	printf("%d\n",key);
  return(0);
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
  int getarray(char **content, int ab, int aa, int ia)
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
         aa = getarray(content, ab, aa, ia);
          removespace(content, ab, ia);
         
         ia++;
        }

       /*else if (content[ab][0] == 'F')
        else if (content[ab][0] == 'C')*/
        ab++;
      }
      //printf("%s",content[21]); 
      //get_resolution(content);
      //get_textures(content);
  }
//   int sqr(int X, int Y, int color)
// {
//     int i;
//     int j;
//     j = 0;
//     i = 0;
//     while (j < g_data.reso_two / 23)
//     {
//         i = 0;
//         while (i < g_data.reso_one / 27)
//         {
//             mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, X + i, Y + j, color);
//             i++;
//         }
//         j++;
//     }
//     return (i);
// }

void player(int Y, int X, int color)
{
    int x = X;
    int y = Y;
    int lenx = 0;
    int leny = 0;
    while (lenx < 6)
    {
      while (leny < 6)
      {
        mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, x, y, color);
        leny++;
        y++;
      }
      leny = 0;
      y = Y;
      lenx++;
      x++;
    }
}

void sqr(int Y, int X, int color)
{
    int x = X;
    int y = Y;
    int lenx = 0;
    int leny = 0;
    while (lenx < tile_size)
    {
      while (leny < tile_size)
      {
        mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, x, y, color);
        leny++;
        y++;
      }
      leny = 0;
      y = Y;
      lenx++;
      x++;
    }
}
  int main()
  {
  get_settings();
  g_mlx.mlx_ptr = mlx_init();
  g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr,g_data.reso_one,g_data.reso_two,"Maro");
  int i;
  int j;
  int b;
  int tile_i;
  int tile_j;
  int a = a;
  b = 0;
  j = 0;
  i = 0;
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
  {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  };

   while (i < 23)
   {  
    while (j < 27)
    {
      tile_i = i * tile_size + 80;
      tile_j = j * tile_size + 80;
        if (map[i][j] == 1)
        {
          sqr(tile_i,tile_j,AQUA);
        }
        if (map[i][j] == 3)
        {
          player(tile_i,tile_j,RED);
        }
        j++;
    }
   j = 0;
   i++;
 }
 
	mlx_key_hook(g_mlx.win_ptr,deal_key,(void *)0);
	mlx_loop(g_mlx.mlx_ptr);
return(0);
}
