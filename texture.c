/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:07:35 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 04:07:36 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

void	check_tex(char **text2, int check)
{
	int i;

	i = 0;
	while ("xpm"[i] != '\0' && check == 1)
	{
		if (text2[1][i] != "xpm"[i] || ft_strlen(text2[1]) != 3)
		{
			ft_putstr("Error\nUse XPM");
			exit(1);
		}
		i++;
	}
	i = 0;
	if (check == 1)
	{
		while (text2[i] != NULL)
		{
			free(text2[i]);
			i++;
		}
		free(text2);
	}
}

void	get_texture_error(char *text)
{
	char	**text2;
	int		i;
	int		check;

	i = 1;
	check = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '.' && text[i + 1] != '\0' && text[i + 1] == 'x')
		{
			check = 1;
		}
		i++;
	}
	if (check == 1)
		text2 = ft_split(text, '.');
	else
		text2 = NULL;
	check_tex(text2, check);
}

char	*get_texture2(char **content, int i, int a, int ab)
{
	char *text1;
	char *text;

	text = ft_substr(content[ab], i, a);
	text1 = ft_strtrim1(text, " ");
	get_texture_error(text1);
	return (text1);
}

char	*get_texture(char **content, int ab)
{
	int		i;
	int		a;
	int		b;
	char	*text1;

	g_check.settings++;
	a = 0;
	if (content[ab][0] == 'S' && content[ab][1] == ' ')
		i = 2;
	else
		i = 3;
	if (i == 2)
		b = 1;
	else
		b = 2;
	if (content[ab][1] == '\0')
		error_msg();
	if (content[ab][b] != ' ')
		error_msg();
	while (content[ab][a] != '\0')
		a++;
	text1 = get_texture2(content, i, a, ab);
	return (text1);
}

void	get_settings_texture(char **content, int ab)
{
	if (content[ab][0] == 'N' && content[ab][1] == 'O')
	{
		g_data.no = get_texture(content, ab);
		g_check.no++;
	}
	else if (content[ab][0] == 'S' && content[ab][1] == 'O')
	{
		g_data.so = get_texture(content, ab);
		g_check.so++;
	}
	else if (content[ab][0] == 'W' && content[ab][1] == 'E')
	{
		g_data.we = get_texture(content, ab);
		g_check.we++;
	}
	else if (content[ab][0] == 'E' && content[ab][1] == 'A')
	{
		g_data.ea = get_texture(content, ab);
		g_check.ea++;
	}
	else if (content[ab][0] == 'S')
	{
		g_data.s = get_texture(content, ab);
		g_check.s++;
	}
}
