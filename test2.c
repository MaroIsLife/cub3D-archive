//  #include "cub3d.h"
 

//  void error_two()
// {
//   int a;
//   int j;
//   int b;

//   a = 0;
//   b = 0;
//   j = 0;

//   while (g_data.map[b + 1] != NULL)
//   {
//     while (g_data.map[b][a] != '\0')
//     a++;

//     while (g_data.map[b + 1][j] != '\0')
//     j++;

//     if (j > a)
//     {
//       while (a < j && g_data.map[b + 1][a] != '\0')
//       {
//         if (g_data.map[b + 1][a] == '0')
//         {
//           perror("Found 0 outbounds");
//           exit(-1);
//         }
//         a++;
//       }
//     }
//     a = 0;
//     j = 0;
//     b++;
//   }
// }
 
//   void check_map()
// {

//   int i;
//   int j;
//   double tile_i;
//   double tile_j;
//   j = 0;
//   i = 0;

//    while (i < g_data.ver) // < ver
//    {  
//     while (j < g_data.hor) // < hor
//     {
//       tile_i = ((double)i + 0.5) * TILE_SIZE;
//       tile_j = ((double)j + 0.5) * TILE_SIZE;
//        if (g_data.map[i][j] == 'N' | g_data.map[i][j] == 'W' || g_data.map[i][j] == 'S' || g_data.map[i][j] == 'E')
//        {
//          g_player.found = 1;
//           if (g_data.map[i][j] == 'N')
//             g_player.rotationAngle = 90;
//           else if (g_data.map[i][j] == 'W')
//             g_player.rotationAngle = 180;
//           else if (g_data.map[i][j] == 'S')
//             g_player.rotationAngle = 270;
//           else if (g_data.map[i][j] == 'E')
//             g_player.rotationAngle = 360;

//           g_player.x = tile_j;
//           g_player.y = tile_i;
//          g_data.map[i][j] = '0';
//         }
//         j++;
//     }
//    j = 0;
//    i++;
//   }
//      if(g_player.found == 0)
//  {
//   perror("No Player found");
//   exit(1);
//  }
// }
  
  
//   void get_resolution(char **content, int ab)
//   {
//     int i;
//     int a;
//     int b;
//     char *r_one;
//     char *r_two;
//     i = 2;
//     a = 0;
//     while (content[ab][i++] != ' ')
//       a++;
//     r_one = ft_substr(content[0],2,a);
//     a = 0;
//     b = i;
//     while(content[0][i++] != '\0')
//         a++;
//     r_two = ft_substr(content[0],b,a);
//     g_data.reso_one = atoi(r_one);
//     g_data.reso_two = atoi(r_two);
//     free(r_one);
//     free(r_two);
//   }

//   char **get_line()
//   {
//     char *line;
//     char **content;
//     int fd;
//     int i;
//     i = 0;
//     fd = open("map.cub",O_RDONLY);
//     content = malloc(30 * sizeof(char *));

//     while (get_next_line(fd,&line))
//     {
//       if (*line == 0)
//         free(line);
//       else if (line != '\0')
//         content[i++] = line;
//       else
//       {
//         perror("Error:");
//         exit(1);
//       }
//     }
//     content[i] = line;
//     i++;
//     content[i] = NULL;
//     return (content);
//   }


//     // while (content[fhor] != NULL)
//     // {
//     //   while (content[fhor][i] != '\0')
//     //     i++;
//     //   if (i > g_data.hor)
//     //     g_data.hor = i;

//     //     i = 0;
//     //     fhor++;
//     // }
//     // i = 0;
//     // while (i < ver)
//     // {
//     //  g_data.map[i++] = calloc((hor + 1),sizeof(char));
//     // }
//   char *get_texture(char **content, int ab)
//   {
//     int i;
//     int a;
//     char *text;

//     a = 0;
//     if (content[ab][0] == 'S')
//     i = 2;
//     else
//     i = 3;
//     while (content[ab][a] != '\0')
//     a++;
//     text = ft_substr(content[ab],i,a);

//    return(text);
//   }
  
//   int getarray(char **content, int ab, int aa)
//   {
//     int hor;
//     int ver;
//     int i;
//     int fhor;

//     if (aa == 1)
//     return (1);
//     g_data.mapstart = ab;
//     i = 0;
//     hor = 0;
//     ver = ab;
//     while (content[ver] != NULL)
//       ver++;
//     ver = ver - ab;
//     g_data.ver = ver;
//     g_data.map = malloc((ver + 1)  * sizeof(char *));
//     g_data.map[ver] = NULL;
//     fhor = ab;
//     while (content[fhor] != NULL)
//     {
//       while (content[fhor][i] != '\0')
//         i++;
//       if (i > g_data.hor)
//         g_data.hor = i;

//         i = 0;
//         fhor++;
//     }
//     i = 0;
//     while (i < ver)
//     {
//      g_data.map[i++] = calloc((g_data.hor + 1),sizeof(char));
//     }
//     return (1);
//   }


//     void int_map(char **content)
//     {
//       int a;
//       int i;
//       int b;

//       a = g_data.mapstart;
//       b = 0;
//       i = 0;
//       while (content[a] != NULL)
//       {
//         while (content[a][i] != '\0')
//         {
//           g_data.map[b][i] = content[a][i];
//           i++;
//         }
//         printf("%s\n",g_data.map[b]);
//         a++;
//         b++;
//         i = 0;
//       }
//     }

//   void get_settings()
//   {
//     char **content;
//     int ab;
//     int aa;
//     int ia;
    
//     ia = 0;
//     aa = 0;
//     ab = 0;

//       content = get_line();
//       while (content[ab] != NULL)
//       {
//         if (content[ab][0] == 'R')
//         get_resolution(content, ab);
//         else if (content[ab][0] == '1')
//         {
//          aa = getarray(content, ab, aa);
//          ia++;
//         }
//         ab++;
//       }

//       int_map(content);
//       // int abs = 0;
//       // while (g_data.map[abs] != NULL)
//       // {
//       //   printf("%s\n",g_data.map[abs]);
//       //   abs++;
//       // }
//   }

//   int main()
//   {
//     get_settings();
//     check_map();
//     error_two();

//     int i = 0;

//     return (0);

//   }