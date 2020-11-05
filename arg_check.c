# include "cub3d.h"


void  arg_check2(char *s1, char **s2)
{
    int i;

    i = 0;
    while (s2[1][i] != '\0')
    {
      if (s2[1][i] != "cub"[i])
      {
        perror("Please Insert the correct map using .cub");
        exit(1);
      }
      i++;
     }
    g_data.mapName = s1;

    i = 0;
    while (s2[i] != NULL)
    {
      free(s2[i]);
      i++;
    }
    free(s2);
}


void  arg_check(char *s1)
  {
    int i;
    char **s2;
    int a;

    a = 0;
    i = 0;
    while (s1[i] != '\0')
    {
      if (s1[i] == '.' && s1[i + 1] != '\0' && s1[i + 1] != '.')
      {
        a = 1;
        s2 = ft_split(s1,'.');           
      }
      i++;
    }
    if (a == 0)
    {
      perror("Please insert the correct map that ends with .cub");
      exit(1);
    }
    arg_check2(s1,s2);
  }

void arg_save_check(char *save)
{
  int i;

  i = 0;
  while ("--save"[i] != '\0')
  {
    if (save[i] != "--save"[i])
    {
      perror("Wrong flag");
      exit(1);
    }
    i++;
  }
  g_player.saved = 1;
}