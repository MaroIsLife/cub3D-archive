#include "cub3d.h"

void get_texture_error(char *text)
{
  char **text2;
  int i;
  int check;

    i = 1;
    check = 0;
  while (text[i] != '\0')
  {
    if (text[i] == '.')
    {
      check = 1;
    }
    i++;
  }
  if (check == 1)
    text2 = ft_split(text,'.');
  else
    text2 = NULL;
    i = 0;
    while ("xpm"[i] != '\0' && check == 1)
    {
      if (text2[1][i] != "xpm"[i] || ft_strlen(text2[1]) != 3)
      {
        perror("Error\nUse XPM");
        exit(1);
      }
      i++;
     }
     if (check == 1)
     {
      free(text2[0]);
      free(text2[1]);
      free(text2);
     }
}

char *get_texture2(char **content,int i, int a, int ab)
{
    char *text1;
    char *text;

    text = ft_substr(content[ab],i,a);
    text1 = ft_strtrim(text," ");
    get_texture_error(text1);
    free(text);

    return (text1);
}


 char *get_texture(char **content, int ab)
  {
    int i;
    int a;
    int b;
    char *text1;
  

    g_check.settings++;
    a = 0;
    if (content[ab][0] == 'S' && content[ab][1] == ' ')
    i = 2;
    else
    i = 3;
    if (i == 2)
    b = 1;
    else
    b = 2;
    if (content[ab][b] != ' ')
    {
      perror("Error\nMissing Space");
      exit(1);
    } 
    while (content[ab][a] != '\0')
    a++;
    text1 = get_texture2(content, i, a, ab);
     return (text1);
  }

  void get_settings_texture(char **content,int ab)
{
     if (content[ab][0] == 'N' && content[ab][1] == 'O')
     {
          g_data.NO = get_texture(content, ab);
          g_check.NO++;
     }
        else if (content[ab][0] == 'S' && content[ab][1] == 'O')
        {
          g_data.SO = get_texture(content, ab);
          g_check.SO++;
        }
        else if (content[ab][0] == 'W' && content[ab][1] == 'E')
        {
          g_data.WE = get_texture(content, ab);
          g_check.WE++;
        }
        else if (content[ab][0] == 'E' && content[ab][1] == 'A')
        {
          g_data.EA = get_texture(content, ab);
          g_check.EA++;
        }
        else if (content[ab][0] == 'S')
        {
          g_data.S = get_texture(content, ab);
          g_check.S++;
        }
}