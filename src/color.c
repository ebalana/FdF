/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:12:38 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 13:31:31 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_low_color(double h, int *r, int *g, int *b)
{
	*r = 0;
	*b = 255;
	*g = (int)(h * 4 * 255);
}

void	set_mid_low_color(double h, int *r, int *g, int *b)
{
	*r = (int)((h - 0.25) * 4 * 255);
	*b = (int)((0.5 - h) * 2 * 255);
	*g = 255;
}

void	set_mid_high_color(double h, int *r, int *g, int *b)
{
	*r = 255;
	*g = (int)((0.75 - h) * 4 * 255);
	*b = 0;
}

int	calculate_color(double normalized_height)
{
	int	red;
	int	green;
	int	blue;

	red = 0;
	green = 0;
	blue = 0;
	if (normalized_height <= 0.25)
		set_low_color(normalized_height, &red, &green, &blue);
	else if (normalized_height <= 0.5)
		set_mid_low_color(normalized_height, &red, &green, &blue);
	else if (normalized_height <= 0.75)
		set_mid_high_color(normalized_height, &red, &green, &blue);
	else
		red = 255;
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}
