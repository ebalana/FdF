/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:09:37 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/29 18:43:13 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	check_line(t_point2d p0, t_point2d p1, t_line *line)
{
	line->dx = abs(p1.x - p0.x);
	line->dy = abs(p1.y - p0.y);
	line->err = line->dx - line->dy;
	if (p0.x < p1.x)
		line->sx = 1;
	else
		line->sx = -1;
	if (p0.y < p1.y)
		line->sy = 1;
	else
		line->sy = -1;
}

void	pline(t_point2d p0, t_point2d p1, mlx_image_t *img, t_line *line)
{
	int	e2;

	while (1)
	{
		if (p0.x >= 0 && p0.x < WIDTH && p0.y >= 0 && p0.y < HEIGHT)
			mlx_put_pixel(img, p0.x, p0.y, p0.rgba);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = line->err * 2;
		if (e2 > -line->dy)
		{
			line->err -= line->dy;
			p0.x += line->sx;
		}
		if (e2 < line->dx)
		{
			line->err += line->dx;
			p0.y += line->sy;
		}
	}
}

void	draw_line(t_point2d p0, t_point2d p1, mlx_image_t *image)
{
	t_line	line;

	check_line(p0, p1, &line);
	pline(p0, p1, image, &line);
}
