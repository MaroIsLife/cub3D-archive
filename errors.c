#include "cub3d.h"
void all_errors()
{
  error_other();
  error_one();
  error_two();
  error_three();
  error_four();
  error_up_down();
  error_first_last();
}
void error_one()
{
  int i;

  i = 0;
  while (g_data.map[0][i] != '\0')
  {
    if (g_data.map[0][i] != '1' && g_data.map[0][i] != 32)
    {
      perror("Error\nInvalid Map (First Line)");
      exit(1);
    }
      i++;
  }
  i = 0;
  while (g_data.map[g_data.ver - 1][i] != '\0')
  {
    if (g_data.map[g_data.ver - 1][i] != '1' && g_data.map[g_data.ver - 1][i] != 32)
    {
      perror("Error\nInvalid Map (Last Line)");
      exit(1);
    }
    i++;
  }
  if (g_check.R > 1 || g_check.NO > 1 || g_check.SO > 1 || g_check.WE > 1 
  || g_check.EA > 1 || g_check.S > 1 || g_check.F > 1 || g_check.C > 1 )
  {
    perror("Error\nDuplicate Settings");
    exit(1);
  }

  }

void error_first_last()
{
  int i;
  int a;

  i = 0;
  a = 0;


  while (g_data.map[i] != NULL)
 {
   if (g_data.map[i][a] == 32)
   {
      while (g_data.map[i][a] == 32)
      a++;
   }
   if (g_data.map[i][a] != '1')
   {
     if (g_data.map[i][a] == '\0')
        break ;
     perror("Error\nFirst Col doesn't start with 1");
     exit(-1);
   }
   i++;
   a = 0;
  }
  a = 0;
  i = 0;
 
}

void error_three()
{

int a;
int i;


  a = 0;
  i = 0;
  while (g_data.map[i] != NULL)
  {
    while (g_data.map[i][a] != '\0')
      a++;

    a--;
    if (g_data.map[i][a] == 32)
    {
      while(g_data.map[i][a] == 32)
      a--;
    }
    if (g_data.map[i][a] != '1')
    {
      if (g_data.map[i][a] == '\0')
        break ;
      perror("Error\nLast Line doesn't end with 1");
      exit(1);
    }
    i++;
    a = 0;
  }
}


 void error_four()
{
  int a;
  int j;
  int b;

  a = 0;
  b = 0;
  j = 0;

  while (g_data.map[b + 1] != NULL)
  {
    while (g_data.map[b][a] != '\0')
    a++;

    while (g_data.map[b + 1][j] != '\0')
    j++;

    if (a > j)
    {
      while (a > j && g_data.map[b][j] != '\0')
      {
        if (g_data.map[b][j] == '0' || g_data.map[b][j] == g_player.pos)
        {
          perror("Error\nFound 0 outbounds space under 0");
          exit(-1);
        }
        j++;
      }
    }
    a = 0;
    j = 0;
    b++;
  }
}


 void error_two()
{
  int a;
  int j;
  int b;

  a = 0;
  b = 0;
  j = 0;

  while (g_data.map[b + 1] != NULL)
  {
    while (g_data.map[b][a] != '\0')
    a++;

    while (g_data.map[b + 1][j] != '\0')
    j++;

    if (j > a)
    {
      while (j > a && g_data.map[b + 1][a] != '\0')
      {
        if (g_data.map[b + 1][a] == '0' || g_data.map[b + 1][a] == g_player.pos)
        {
          perror("Error\nFound 0 or Player   outbounds");
          exit(-1);
        }
        a++;
      }
    }
    a = 0;
    j = 0;
    b++;
  }
}

void error_up_down()
{
  int i;
  int j;
  int a;
  int b;

  a = 0;
  j = 0;
  i = 0;
  b = 0;
  while (g_data.map[i] != NULL)
  {
    while (g_data.map[i][a] != '\0')
    {
      if ((g_data.map[i + 1] != NULL && g_data.map[i + 1][a] == 32) && (g_data.map[i][a] == '0' || g_data.map[i][a] == 'N'))
      {
        perror("Error\nan Open 0 or 2 inbound");
        exit(1);
      }
      else if (g_data.map[i] != NULL && g_data.map[i - b][a] == 32 && (g_data.map[i][a] == '0' || g_data.map[i][a] == g_player.pos))
      {
        perror("Error\n space upside 0");
        exit(1);
      }
      a++;
    }
    b = 1;
    a = 0;
    i++;
  }
  i = 0;
  while (g_data.map[i] != NULL)
  {
    while (g_data.map[i][a] != '\0')
    {
      if ((g_data.map[i][a] == '0' && g_data.map[i][a + 1] == 32) || (g_data.map[i][a] == '2' && g_data.map[i][a + 1] == 32)
      || (g_data.map[i][a] == g_player.pos && g_data.map[i][a - 1] == 32))
      {
        perror("Error\n space after 0 or 2 ");
        exit(-1);
      }
      else if ((g_data.map[i][a] == '0' && g_data.map[i][a - 1] == 32) || (g_data.map[i][a] == '2' && g_data.map[i][a - 1] == 32)
    || (g_data.map[i][a] == g_player.pos && g_data.map[i][a - 1] == 32))
      {
        perror("Error\n space before 0 or 2");
        exit(-1);
      }
      a++;

    }
    i++;
    a = 0;
  }

}



