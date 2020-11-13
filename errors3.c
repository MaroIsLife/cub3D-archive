/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:17:34 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:17:36 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	error_four(void)
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
		while (a > j && g_data.map[b][j] != '\0')
		{
			if (g_data.map[b][j] == '0' || g_data.map[b][j] == g_player.pos
			|| g_data.map[b][j] == '2')
				error_msg();
			j++;
		}
		a = 0;
		j = 0;
		b++;
	}
}

void	error_two(void)
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
		while (j > a && g_data.map[b + 1][a] != '\0')
		{
			if (g_data.map[b + 1][a] == '0' ||
			g_data.map[b + 1][a] == g_player.pos
			|| g_data.map[b + 1][a] == '2')
				error_msg();
			a++;
		}
		a = 0;
		j = 0;
		b++;
	}
}

void	error_six(void)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (g_data.map[i] != NULL)
	{
		while (g_data.map[i][a] != '\0')
		{
			if ((g_data.map[i][a] == '0' && g_data.map[i][a + 1] == 32) ||
			(g_data.map[i][a] == '2' && g_data.map[i][a + 1] == 32)
			|| (g_data.map[i][a] == g_player.pos && g_data.map[i][a - 1] == 32))
				error_msg();
			else if ((g_data.map[i][a] == '0' && g_data.map[i][a - 1] == 32) ||
			(g_data.map[i][a] == '2' && g_data.map[i][a - 1] == 32)
		|| (g_data.map[i][a] == g_player.pos && g_data.map[i][a - 1] == 32))
				error_msg();
			a++;
		}
		i++;
		a = 0;
	}
}

void	error_five(void)
{
	int i;
	int a;
	int b;

	a = 0;
	i = 0;
	b = 0;
	while (g_data.map[i] != NULL)
	{
		while (g_data.map[i][a] != '\0')
		{
			if ((g_data.map[i + 1] != NULL && g_data.map[i + 1][a] == 32)
			&& (g_data.map[i][a] == '0' || g_data.map[i][a] == g_player.pos
		|| g_data.map[i][a] == '2'))
				error_msg();
			else if (g_data.map[i] != NULL && g_data.map[i - b][a] == 32
			&& (g_data.map[i][a] == '0'
			|| g_data.map[i][a] == g_player.pos || g_data.map[i][a] == '2'))
				error_msg();
			a++;
		}
		b = 1;
		a = 0;
		i++;
	}
}

void	error_last(void)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (g_data.map[i] != NULL)
	{
		while (g_data.map[i][a] != '\0')
			a++;
		if (g_data.map[i][a - 1] == '0' || g_data.map[i][a - 1] == g_player.pos
		|| g_data.map[i][a - 1] == '2')
			error_msg();
		i++;
		a = 0;
	}
}
