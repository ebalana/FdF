/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:50:19 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 17:07:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	calculate_min_max_heights(t_map *map)
{
	int	x;
	int	y;
	int	height;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			height = map->values[y][x];
			if (height < map->z_min)
				map->z_min = height;
			if (height > map->z_max)
				map->z_max = height;
			x++;
		}
		y++;
	}
}

t_point3d	rotate_z(t_point3d point3d, double alpha)
{
	t_point3d	rotated_point;

	rotated_point.x = point3d.x * cos(alpha) - point3d.y * sin(alpha);
	rotated_point.y = point3d.x * sin(alpha) + point3d.y * cos(alpha);
	rotated_point.z = point3d.z;
	return (rotated_point);
}

void	draw_connections(t_fdf *fdf, int x, int y, t_point2d p2d_0)
{
	t_point3d	p1;
	t_point2d	p2d_1;
	double		alpha;

	alpha = fdf->map->alpha;
	if (x < fdf->map->width - 1)
	{
		p1 = (t_point3d){x + 1, y, fdf->map->values[y][x + 1]};
		p1 = rotate_z(p1, alpha);
		p2d_1 = project_point(p1, fdf->map);
		draw_line(p2d_0, p2d_1, fdf->image);
	}
	if (y < fdf->map->height - 1)
	{
		p1 = (t_point3d){x, y + 1, fdf->map->values[y + 1][x]};
		p1 = rotate_z(p1, alpha);
		p2d_1 = project_point(p1, fdf->map);
		draw_line(p2d_0, p2d_1, fdf->image);
	}
}

void	draw_map(t_fdf *fdf)
{
	int			x;
	int			y;
	t_point3d	p0;
	t_point2d	p2d_0;

	if (!fdf || !fdf->map || !fdf->map->values)
		handle_error(INVALID_MAP);
	calculate_min_max_heights(fdf->map);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			p0 = (t_point3d){x, y, fdf->map->values[y][x]};
			p0 = rotate_z(p0, fdf->map->alpha);
			p2d_0 = project_point(p0, fdf->map);
			draw_connections(fdf, x, y, p2d_0);
			x++;
		}
		y++;
	}
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
}
