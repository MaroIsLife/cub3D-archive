#include "cub3d.h"

void get_resoError(char **content,int ab)
{
  int i;
  int b;

  i = 1;
  b = 0;
   if (content[ab][1] != ' ')
    {
      perror("Error\nMissing Space");
      exit(1);
    }
    while (content[ab][i] != '\0')
    {
      if (content[ab][i] >= 58 && content[ab][i] <= 126)
      {
        perror("Error\n Wrong character In resolution");
        exit(1);
      }
      i++;
    }
}


void get_resolution(char **content, int ab)
  {
    int i;
    int a;
    int b;
    char *r_one;
    char *r_two;

    get_resoError(content,ab);
    g_check.R++;
    g_check.settings++;
    i = 1;
    a = 0;
    while (content[ab][i] == ' ')
      i++;
      b = i;
      while (content[ab][b] != ' ')
      {
        b++;
        a++;
      }
    r_one = ft_substr(content[ab],i,a);
    a = 0;
    b = i;
    while(content[ab][i++] != '\0')
        a++;
    r_two = ft_substr(content[ab],b,a);
    g_data.reso_one = ft_atoi(r_one);
    g_data.reso_two = ft_atoi(r_two);
    free(r_one);
    free(r_two);
  } 