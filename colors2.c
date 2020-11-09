/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:01:22 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 01:01:23 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_colorr(char **content, int b, int i, int ab)
{
	char *s;

	s = ft_substr(content[ab], b, i);
	g_color.r = ft_atoi(s);
	free(s);
}

void	get_colorg(char **content, int b, int i, int ab)
{
	char *s;

	s = ft_substr(content[ab], b, i);
	g_color.g = ft_atoi(s);
	free(s);
}

void	get_colorb_error(char **content, int b, int i, int ab)
{
	char *s;

	b = g_a + 1;
	g_a++;
	i = 0;
	while (content[ab][g_a++] != '\0')
		i++;
	s = ft_substr(content[ab], b, i);
	g_color.b = ft_atoi(s);
	free(s);
	get_color_b_error2(content, ab);
}
