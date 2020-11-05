#include "cub3d.h"


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

void get_colorR(char **content, int b,int i,int ab)
{
    char *s;

    s = ft_substr(content[ab],b,i);
    g_color.r = ft_atoi(s);
    free(s);
}

void get_colorG(char **content, int b,int i,int ab)
{
    char *s;

    s = ft_substr(content[ab],b,i);
    g_color.g = ft_atoi(s);
    free(s);   
}

void get_colorB_error(char **content, int b,int i,int ab)
{
    char *s;



    s = ft_substr(content[ab],b,i);
    g_color.b = ft_atoi(s);
    free(s);

    if (g_color.b < 0 || g_color.g < 0 || g_color.r < 0)
  {
    perror("Negative number");
    exit (-1);
  }
     if (g_color.b > 255 || g_color.g > 255 || g_color.r > 255)
  {
    perror("Max number");
    exit (-1);
  }   
}




int get_color(char **content, int ab)
{
  int i;
  int a;
  int b;

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
  get_colorR(content, b, i, ab);
  b = a + 1;
  a++;
  i = 0;
  while (content[ab][a] != ',')
  {
    i++;
    a++;
  }
  get_colorG(content, b, i, ab);
  b = a + 1;
  a++;
  i = 0;
  while (content[ab][a++] != '\0')
    i++;
  get_colorB_error(content, b, i, ab);
    return (g_color.b + g_color.g * 256 + g_color.r * 65536);
}