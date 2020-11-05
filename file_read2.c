#include "cub3d.h"


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
    fd = open(g_data.mapName,O_RDONLY);
    if (fd == -1)
    {
      perror("The Map could not be found.");
      exit(-1);
    }
    content = malloc(100 * sizeof(char *));

    while (get_next_line(fd,&line))
    {
      // if (*line == 0)
      //   free(line);
      if (line != '\0')
        content[i++] = line;
      else
      {
        perror("Error\n");
        exit(1);
      }
    }
    content[i] = line;
    i++;
    content[i] = NULL;
    return (content);
  }