#include "cub3d.h"

void open_txt(char *txt)
{
    int fd;

    fd = open(txt,O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nTexture cannot be found");
        exit (-1);
    }
    close(fd);
}

void error_other()
{
    int i;
    int a;
    
    i = 0;
    a = 0;
    while (g_data.map[i] != NULL)
    {
        while (g_data.map[i][a] != '\0')
        {
            if (g_data.map[i][a] != ' ' && g_data.map[i][a] != '1' && g_data.map[i][a] != '0'
             && g_data.map[i][a] != '2' && g_data.map[i][a] != 'N' && g_data.map[i][a] != 'S'
             && g_data.map[i][a] != 'W' && g_data.map[i][a] != 'E')
             {
                 perror("Error\n Wrong Character in map");
                 exit (1);
             }
             a++;
        }
        a = 0;
        i++;
    }
    }