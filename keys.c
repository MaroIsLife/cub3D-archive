# include "cub3d.h"

int keyPress(int key)
{
if (key == 13) //UP
      g_player.walkDirection = 1;
if (key == 2)
{
      g_player.directionLR = 90;
      g_player.walkDirection = 1;
}
if (key == 0)
{
  g_player.directionLR = 270;
  g_player.walkDirection = 1;
}
if (key == 1) 
      g_player.walkDirection = -1;

if (key == 123) //L
      g_player.turnDirection = -1;

if (key == 124) //R
      g_player.turnDirection = 1;
if (key == 53)
      {
        mlx_destroy_window(g_mlx.mlx_ptr,g_mlx.win_ptr);
        exit(1);
      } 
      return (0);
}

int keyRelease(int key)
{
  if (key == 13) //UP
      g_player.walkDirection = 0;
    if (key == 1) //D
      g_player.walkDirection = 0;
    if (key == 2)
    {
      g_player.directionLR = 0;
      g_player.walkDirection = 0;
    }
    if (key == 0)
    {
      g_player.directionLR = 0;
      g_player.walkDirection = 0;
    }
    if (key == 123) //L
      g_player.turnDirection = 0;
    if (key == 124) //R
      g_player.turnDirection = 0;
      return (0);
}

int red()
{
    exit(1);
}