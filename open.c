#include "cub3d.h"

void open_txt(char *txt)
{
    int fd;

    fd = open(txt,O_RDONLY);
    if (fd == -1)
    {
        perror("Texture cannot be found");
        exit (-1);
    }
    close(fd);
}