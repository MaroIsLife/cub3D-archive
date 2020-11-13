/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:22:29 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 02:22:30 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color_b_error3(char **content, int ab, int c)
{
	if (content[ab][1] != ' ' || c != 2)
	{
		ft_putstr("Error\n");
		exit(1);
	}
}

void	get_color_b_error2(char **content, int ab)
{
	int a;
	int c;

	c = 0;
	a = 2;
	if (g_color.b > 255 || g_color.g > 255 || g_color.r > 255)
	{
		ft_putstr("Error\nMax number");
		exit(-1);
	}
	while (content[ab][a] != '\0')
	{
		if (content[ab][a] == ',')
			c++;
		if ((content[ab][a] > 65 && content[ab][a] < 122) ||
		content[ab][a] == '-')
		{
			ft_putstr("Error\n Negative number or Undefined character");
			exit(1);
		}
		a++;
	}
	get_color_b_error3(content, ab, c);
}

int		count_color(char **content, int ab)
{
	int a;
	int i;

	i = 0;
	a = 0;
	g_check.settings++;
	while ((content[ab][a] < 48 || content[ab][a] > 57)
	&& content[ab][a] != '\0')
		a++;
	if (content[ab][a] < 48 || content[ab][a] > 57)
	{
		ft_putstr("Error\nEmpty Settings");
		exit(1);
	}
	return (a);
}

int		get_color(char **content, int ab)
{
	int i;
	int b;

	i = 0;
	g_a = count_color(content, ab);
	b = g_a;
	while (content[ab][g_a] != ',')
	{
		i++;
		g_a++;
	}
	get_colorr(content, b, i, ab);
	b = g_a + 1;
	g_a++;
	i = 0;
	while (content[ab][g_a] != ',')
	{
		i++;
		g_a++;
	}
	get_colorg(content, b, i, ab);
	get_colorb_error(content, b, i, ab);
	return (g_color.b + g_color.g * 256 + g_color.r * 65536);
}
