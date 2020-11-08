#include "cub3d.h"
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

  get_color_B_error2(content,ab);
}