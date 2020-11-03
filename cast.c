#include "cub3d.h"


  float normalizeAngle(float angle)
  {
    angle = remainderf(angle,360);
    if (angle < 0)
    {
      angle = (360) + angle;
    }
    return (angle);
  }

void h_calc()
{
    while (is_wall(g_var.xintercept, g_var.yintercept))
	{
		g_var.xintercept += g_var.xstep;
		g_var.yintercept += g_var.ystep;
	}
	if (g_var.isRayFacingUp)
		g_var.yintercept++;
	g_var.hitx1 = g_var.xintercept;
	g_var.hity1 = g_var.yintercept;
	g_var.distanceHor = (float)sqrt((g_var.hitx1 - g_player.x) *
		(g_var.hitx1 - g_player.x) + (g_var.hity1 - g_player.y) *
		(g_var.hity1 - g_player.y));


}

void v_calc()
{

    while (is_wall(g_var.xintercept, g_var.yintercept))
	{
		g_var.xintercept += g_var.xstep;
		g_var.yintercept += g_var.ystep;
	}
	if (g_var.isRayFacingLeft)
		g_var.xintercept++;
	g_var.hitx2 = g_var.xintercept;
	g_var.hity2 = g_var.yintercept;
	g_var.distanceVer = (float)sqrt((g_var.hitx2 - g_player.x) *
		(g_var.hitx2 - g_player.x) +
		(g_var.hity2 - g_player.y) * (g_var.hity2 - g_player.y));
}


void h_cast(float rayAngle)
{
    g_var.hitx1 = 0;
	g_var.hity1 = 0;
    g_var.yintercept = (float)floor(g_player.y / TILE_SIZE) * TILE_SIZE;
    if (g_var.isRayFacingDown == 1)
		g_var.yintercept += TILE_SIZE;
    g_var.xintercept = g_player.x +
	(g_var.yintercept - g_player.y) / tan(rayAngle * (M_PI / 180));
    g_var.ystep = TILE_SIZE;
    if (g_var.isRayFacingUp)
		g_var.ystep *= -1;
	g_var.xstep = TILE_SIZE / tan(rayAngle * (M_PI / 180));
	if (g_var.isRayFacingLeft && g_var.xstep > 0)
		g_var.xstep *= -1;
	if (g_var.isRayFacingRight == 1 && g_var.xstep < 0)
		g_var.xstep *= -1;
	g_var.nexthitx = g_var.xintercept;
	g_var.nexthity = g_var.yintercept;
	if (g_var.isRayFacingUp)
		g_var.yintercept--;
     h_calc();   
}

void v_cast(float rayAngle)
{
    g_var.hitx2 = 0;
	g_var.hity2 = 0;
    	g_var.xintercept = (float)floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (g_var.isRayFacingRight == 1)
		g_var.xintercept += TILE_SIZE;
	g_var.yintercept = g_player.y + (g_var.xintercept - g_player.x) *
	tan(rayAngle * (M_PI / 180));
	g_var.xstep = TILE_SIZE;
	if (g_var.isRayFacingLeft)
		g_var.xstep *= -1;
	g_var.ystep = TILE_SIZE * tan(rayAngle * (M_PI / 180));
	if (g_var.isRayFacingUp && g_var.ystep > 0)
		g_var.ystep *= -1;
	if (g_var.isRayFacingDown == 1 && g_var.ystep < 0)
		g_var.ystep *= -1;
	g_var.nexthitx = g_var.xintercept;
	g_var.nexthity = g_var.yintercept;
	if (g_var.isRayFacingLeft)
		g_var.xintercept--;
        v_calc();
}

void calc_dis(float rayAngle,int id)
{
    if (g_var.distanceVer < g_var.distanceHor)
	{
		g_ray[id].hitx = g_var.hitx2;
		g_ray[id].hity = g_var.hity2;
		g_ray[id].offset = (int)g_var.hity2 % TILE_SIZE;
		g_ray[id].wasHitVertical = 1;
		g_var.distance = g_var.distanceVer;
	}
	else
	{
		g_var.distance = g_var.distanceHor;
		g_ray[id].hitx = g_var.hitx1;
		g_ray[id].hity = g_var.hity1;
		g_ray[id].wasHitVertical = 0;
		g_ray[id].offset = (int)g_var.hitx1 % TILE_SIZE;
	}
	g_ray[id].rayAngle = rayAngle;
	g_ray[id].distance = g_var.distance;
	g_ray[id].isRayFacingDown = g_var.isRayFacingDown;
	g_ray[id].isRayFacingUp = g_var.isRayFacingUp;
	g_ray[id].isRayFacingLeft = g_var.isRayFacingLeft;
	g_ray[id].isRayFacingRight = g_var.isRayFacingRight;

}


void cast(float rayAngle,int id)
{
    rayAngle = normalizeAngle(rayAngle);
    g_var.distanceHor = 0;
    g_var.distance = 0;
    g_var.distanceVer = 0;
    g_var.isRayFacingDown = 0;
    g_var.isRayFacingRight = 0;
    if (rayAngle >= 0 && rayAngle <= 180)
		    g_var.isRayFacingDown = 1;
	  if (rayAngle <= 90 || rayAngle >= 270)
		    g_var.isRayFacingRight = 1;

	      g_var.isRayFacingUp = !g_var.isRayFacingDown;
	      g_var.isRayFacingLeft = !g_var.isRayFacingRight;
          h_cast(rayAngle);
          v_cast(rayAngle);
          calc_dis(rayAngle,id);
}