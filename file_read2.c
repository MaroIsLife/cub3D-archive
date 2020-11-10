/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:46:20 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:46:20 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	int_map(char **content)
{
	int a;
	int i;
	int b;

	if (g_check.settings != 9)
	{
		ft_putstr("Error\n Missing Settings");
		exit(1);
	}
	a = g_data.mapstart;
	b = 0;
	i = 0;
	while (content[a] != NULL)
	{
		while (content[a][i] != '\0')
		{
			g_data.map[b][i] = content[a][i];
			i++;
		}
		a++;
		b++;
		i = 0;
	}
}

char	**get_line(void)
{
	char	*line;
	char	**content;
	int		fd;
	int		i;

	i = 0;
	fd = open(g_data.mapname, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error\nThe Map could not be found.");
		exit(1);
	}
	content = malloc(150 * sizeof(char *));
	while (get_next_line(fd, &line))
	{
		if (line != '\0')
			content[i++] = line;
		else
			error_msg();
	}
	content[i] = line;
	i++;
	content[i] = NULL;
	return (content);
}
