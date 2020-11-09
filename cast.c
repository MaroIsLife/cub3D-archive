/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:30:08 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 00:30:11 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	h_cast(float rayangle)
{
	g_var.hitx1 = 0;
	g_var.hity1 = 0;
	g_var.yintercept = (float)floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (g_var.israyfacingdown == 1)
		g_var.yintercept += TILE_SIZE;
	g_var.xintercept = g_player.x +
	(g_var.yintercept - g_player.y) / tan(rayangle * (M_PI / 180));
	g_var.ystep = TILE_SIZE;
	if (g_var.israyfacingup)
		g_var.ystep *= -1;
	g_var.xstep = TILE_SIZE / tan(rayangle * (M_PI / 180));
	if (g_var.israyfacingleft && g_var.xstep > 0)
		g_var.xstep *= -1;
	if (g_var.israyfacingright == 1 && g_var.xstep < 0)
		g_var.xstep *= -1;
	g_var.nexthitx = g_var.xintercept;
	g_var.nexthity = g_var.yintercept;
	if (g_var.israyfacingup)
		g_var.yintercept--;
	h_calc();
}

void	v_cast(float rayangle)
{
	g_var.hitx2 = 0;
	g_var.hity2 = 0;
	g_var.xintercept = (float)floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (g_var.israyfacingright == 1)
		g_var.xintercept += TILE_SIZE;
	g_var.yintercept = g_player.y + (g_var.xintercept - g_player.x) *
	tan(rayangle * (M_PI / 180));
	g_var.xstep = TILE_SIZE;
	if (g_var.israyfacingleft)
		g_var.xstep *= -1;
	g_var.ystep = TILE_SIZE * tan(rayangle * (M_PI / 180));
	if (g_var.israyfacingup && g_var.ystep > 0)
		g_var.ystep *= -1;
	if (g_var.israyfacingdown == 1 && g_var.ystep < 0)
		g_var.ystep *= -1;
	g_var.nexthitx = g_var.xintercept;
	g_var.nexthity = g_var.yintercept;
	if (g_var.israyfacingleft)
		g_var.xintercept--;
	v_calc();
}

void	calc_dis(float rayangle, int id)
{
	if (g_var.distancever < g_var.distancehor)
	{
		g_ray[id].hitx = g_var.hitx2;
		g_ray[id].hity = g_var.hity2;
		g_ray[id].offset = (int)g_var.hity2 % TILE_SIZE;
		g_ray[id].washitvertical = 1;
		g_var.distance = g_var.distancever;
	}
	else
	{
		g_var.distance = g_var.distancehor;
		g_ray[id].hitx = g_var.hitx1;
		g_ray[id].hity = g_var.hity1;
		g_ray[id].washitvertical = 0;
		g_ray[id].offset = (int)g_var.hitx1 % TILE_SIZE;
	}
	g_ray[id].rayangle = rayangle;
	g_ray[id].distance = g_var.distance;
	g_ray[id].israyfacingdown = g_var.israyfacingdown;
	g_ray[id].israyfacingup = g_var.israyfacingup;
	g_ray[id].israyfacingleft = g_var.israyfacingleft;
	g_ray[id].israyfacingright = g_var.israyfacingright;
}

void	cast(float rayangle, int id)
{
	rayangle = normalizeangle(rayangle);
	g_var.distancehor = 0;
	g_var.distance = 0;
	g_var.distancever = 0;
	g_var.israyfacingdown = 0;
	g_var.israyfacingright = 0;
	if (rayangle >= 0 && rayangle <= 180)
		g_var.israyfacingdown = 1;
	if (rayangle <= 90 || rayangle >= 270)
		g_var.israyfacingright = 1;
	g_var.israyfacingup = !g_var.israyfacingdown;
	g_var.israyfacingleft = !g_var.israyfacingright;
	h_cast(rayangle);
	v_cast(rayangle);
	calc_dis(rayangle, id);
}
