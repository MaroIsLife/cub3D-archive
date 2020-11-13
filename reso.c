/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reso.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:53:36 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:53:37 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	get_resoerror(char **content, int ab)
{
	int i;
	int b;

	g_check.settings++;
	i = 1;
	b = 0;
	if (content[ab][1] != ' ')
		error_msg();
	while (content[ab][i] != '\0')
	{
		if (content[ab][i] >= 58 && content[ab][i] <= 126)
		{
			ft_putstr("Error\n Wrong character In resolution");
			exit(1);
		}
		i++;
	}
}

void	free_reso(char *r_one, char *r_two)
{
	g_data.reso_one = ft_atoi(r_one);
	g_data.reso_two = ft_atoi(r_two);
	free(r_one);
	free(r_two);
}

void	get_resolution(char **content, int ab)
{
	int		i;
	int		a;
	int		b;
	char	*r_one;
	char	*r_two;

	get_resoerror(content, ab);
	g_check.r++;
	i = 1;
	a = 0;
	while (content[ab][i] == ' ')
		i++;
	b = i;
	while (content[ab][b] != ' ')
	{
		b++;
		a++;
	}
	r_one = ft_substr(content[ab], i, a);
	a = 0;
	while (content[ab][i++] != '\0')
		a++;
	r_two = ft_substr(content[ab], b, a);
	free_reso(r_one, r_two);
}
