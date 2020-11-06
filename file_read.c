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


 char *get_texture(char **content, int ab)
  {
    int i;
    int a;
    char *text;
    int b;

  
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
    text = ft_substr(content[ab],i,a);
     i = ft_strlen(text);
     if (i == 2 || i == 3)
     {
       perror("Missing Texture");
       exit (1);
     }

   return(text);
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

 void get_settings()
  {
    char **content;
    int ab;
    int aa;
    
    aa = 0;
    ab = 0;
    content = get_line();
    while (content[ab] != NULL)
    {
      if (content[ab][0] == 'R')
        get_resolution(content, ab);
          else if (content[ab][0] == 'F')
          {
            g_data.Fcolor = get_color(content,ab);
            g_check.F++;
          }
          else if (content[ab][0] == 'C')
          {
            g_data.Ccolor = get_color(content,ab);
            g_check.C++;
          }
        else if (content[ab][0] == '1' || content[ab][0] == ' ')
         aa = getarray(content, ab, aa);
        get_settings_texture(content, ab);
        ab++;
      }
      int_map(content);
      ab = 0;
      while (content[ab] != NULL)
      {
        free(content[ab]);
        ab++;
      }
      free(content);
  }