/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:23:29 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:23:30 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

float	normalizeangle(float angle)
{
	angle = remainderf(angle, 360);
	if (angle < 0)
	{
		angle = (360) + angle;
	}
	return (angle);
}

void	h_calc(void)
{
	while (is_wall(g_var.xintercept, g_var.yintercept))
	{
		g_var.xintercept += g_var.xstep;
		g_var.yintercept += g_var.ystep;
	}
	if (g_var.israyfacingup)
		g_var.yintercept++;
	g_var.hitx1 = g_var.xintercept;
	g_var.hity1 = g_var.yintercept;
	g_var.distancehor = (float)sqrt((g_var.hitx1 - g_player.x) *
		(g_var.hitx1 - g_player.x) + (g_var.hity1 - g_player.y) *
		(g_var.hity1 - g_player.y));
}

void	v_calc(void)
{
	while (is_wall(g_var.xintercept, g_var.yintercept))
	{
		g_var.xintercept += g_var.xstep;
		g_var.yintercept += g_var.ystep;
	}
	if (g_var.israyfacingleft)
		g_var.xintercept++;
	g_var.hitx2 = g_var.xintercept;
	g_var.hity2 = g_var.yintercept;
	g_var.distancever = (float)sqrt((g_var.hitx2 - g_player.x) *
		(g_var.hitx2 - g_player.x) +
		(g_var.hity2 - g_player.y) * (g_var.hity2 - g_player.y));
}
