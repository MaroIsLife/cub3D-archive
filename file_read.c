# include "cub3d.h"


int getarray(char **content, int ab, int aa)
  {
    int hor;
    int ver;
    int i;
    int fhor;

    if (aa == 1)
    return (1);
    g_data.mapstart = ab;
    g_check.settings++;
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




char **trim(char **content)
{
  int i;
  int a;

  i = 0;
  a = 0;
  while (content[i] != NULL)
  {
    if (content[i][0] == ' ')
    {
      while (content[i][a] == ' ')
      a++;
      if (content[i][a] == '1')
      break ;
    }
    free(content[i]);
    content[i] = ft_strtrim(content[i]," ");
    i++;
  }
  i = 0;
  return (content);
}

char **get_settings_check(char **content)
{
  int ab;
  int aa;

  ab = 0;
  aa = 0;

  while (content[ab] != NULL)
    {
      if (content[ab][0] == 'R')
        get_resolution(content, ab);
          else if (content[ab][0] == 'F')
          {
            g_data.Fcolor = get_color(content,ab);
            g_check.F++;
            g_check.settings++;
          }
          else if (content[ab][0] == 'C')
          {
            g_data.Ccolor = get_color(content,ab);
            g_check.C++;
            g_check.settings++;
          }
        else if (content[ab][0] == '1' || content[ab][0] == ' ')
         aa = getarray(content, ab, aa);
        get_settings_texture(content, ab);
        ab++;
      }
  return (content);
}

 void get_settings()
  {
    char **content;
    int ab;
    
    ab = 0;
    content = get_line();
    content = trim(content);
    content = get_settings_check(content);
    int_map(content);
      while (content[ab] != NULL)
      {
        free(content[ab]);
        ab++;
      }
      free(content);
  }