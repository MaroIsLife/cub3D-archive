/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:17:10 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:17:11 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	error_msg(void)
{
	ft_putstr("Error\n");
	exit(1);
}

void	error_one(void)
{
	int i;

	i = 0;
	while (g_data.map[0][i] != '\0')
	{
		if (g_data.map[0][i] != '1' && g_data.map[0][i] != 32)
			error_msg();
		i++;
	}
	i = 0;
	while (g_data.map[g_data.ver - 1][i] != '\0')
	{
		if (g_data.map[g_data.ver - 1][i] != '1'
		&& g_data.map[g_data.ver - 1][i] != 32)
			error_msg();
		i++;
	}
	if (g_check.r > 1 || g_check.no > 1 || g_check.so > 1 || g_check.we > 1
	|| g_check.ea > 1 || g_check.s > 1 || g_check.f > 1 || g_check.c > 1)
	{
		ft_putstr("Error\nDuplicate Settings");
		exit(1);
	}
}

void	error_three(void)
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
			ft_putstr("Error\nFirst Col doesn't start with 1");
			exit(-1);
		}
		i++;
		a = 0;
	}
}

void	all_errors(void)
{
	error_other();
	error_one();
	error_six();
	error_two();
	error_three();
	error_four();
	error_five();
	error_last();
}
