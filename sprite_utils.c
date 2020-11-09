/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:57:45 by mougnou           #+#    #+#             */
/*   Updated: 2020/11/09 03:57:45 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cub3d.h"

float	to_rad(float angle)
{
	angle = angle * (M_PI / 180);
	return (angle);
}

float	to_deg(float angle)
{
	angle = angle * (180 / M_PI);
	return (angle);
}
