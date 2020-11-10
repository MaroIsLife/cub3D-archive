/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:19:35 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/08 23:19:37 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	arg_check2(char *s1, char **s2)
{
	int i;

	i = 0;
	while ("cub"[i] != '\0')
	{
		if (s2[1][i] != "cub"[i] || ft_strlen(s2[1]) != 3)
		{
			perror("Error\nPlease Insert the correct map using .cub");
			exit(1);
		}
		i++;
	}
	g_data.mapname = s1;
	i = 0;
	while (s2[i] != NULL)
	{
		free(s2[i]);
		i++;
	}
	free(s2);
}

void	arg_check(char *s1)
{
	int		i;
	char	**s2;
	int		a;

	a = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '.' && s1[i + 1] != '\0' && s1[i + 1] == 'c')
		{
			a = 1;
			s2 = ft_split(s1, '.');
		}
		i++;
	}
	if (a == 0)
	{
		perror("Error\nPlease insert the correct map that ends with .cub");
		exit(1);
	}
	if (s2[1] != NULL)
		arg_check2(s1, s2);
	else
		error_msg();
}

void	arg_save_check(char *save)
{
	int i;

	i = 0;
	while ("--save"[i] != '\0')
	{
		if (save[i] != "--save"[i] || ft_strlen(save) != 6)
		{
			perror("Error\nWrong flag");
			exit(1);
		}
		i++;
	}
	g_player.saved = 1;
}
