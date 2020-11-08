#include "cub3d.h"



void get_color_B_error2(char **content, int ab)
{
  int a;
  int c;

  c = 0;
  a = 2;
  
  if (g_color.b > 255 || g_color.g > 255 || g_color.r > 255)
  {
    perror("Error\nMax number");
    exit (-1);
  }
  while (content[ab][a] != '\0')
  {
    if (content[ab][a] == ',')
    c++;
    if ((content[ab][a] > 65 && content[ab][a] < 122) || content[ab][a] == '-')
    {
      perror("Error\n Negative number or Undefined character");
      exit(1);   
    }
    a++;
  }
  if (content[ab][1] != ' ' || c != 2)
    {
      perror("Error\n");
      exit(1);
    }
}

int count_color(char **content, int ab)
{
  int a;
  int i;

  i = 0;
  a = 0;
   while (content[ab][a] < 48 || content[ab][a] > 57)
    a++;
    if (content[ab][a] < 48 || content[ab][a] > 57)
    {
      perror("Error\nEmpty Settings");
      exit(1);
    }
    return (a);
}




int get_color(char **content, int ab)
{
  int i;
  int a;
  int b;

  i = 0;
  a = count_color(content, ab);
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