/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:32:10 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 12:45:05 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	get_scale(t_map *map)
{
	double	scale_x;
	double	scale_y;

	scale_x = (double)WIDTH / (map->width + map->height);
	scale_y = (double)HEIGHT / (map->width + map->height);
	return (fmin(scale_x, scale_y) * 0.8 * map->zoom);
}

t_point2d	project_flat(t_point3d point3d, double scale, t_map *map)
{
	t_point2d	point2d;

	point2d.x = point3d.x * scale + map->offset_x;
	point2d.y = point3d.y * scale + map->offset_y;
	return (point2d);
}

t_point2d	project_iso(t_point3d point3d, double scale, t_map *map)
{
	t_point2d	point2d;

	point2d.x = (point3d.x - point3d.y) * cos(0.523599) * scale + map->offset_x;
	point2d.y = (point3d.x + point3d.y) * sin(0.523599) * scale
		- point3d.z * scale + map->offset_y;
	return (point2d);
}

t_point2d	project_point(t_point3d point3d, t_map *map)
{
	t_point2d	point2d;
	double		scale;
	double		normalized_height;

	scale = get_scale(map);
	if (map->flat_mode != 1)
		point3d.z *= map->elevation;
	if (map->flat_mode == 1)
		point2d = project_flat(point3d, scale, map);
	else
		point2d = project_iso(point3d, scale, map);
	normalized_height = (point3d.z - map->z_min) / (map->z_max - map->z_min);
	point2d.rgba = calculate_color(normalized_height);
	point2d.z = point3d.z;
	return (point2d);
}
