/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:50:19 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/22 12:24:09 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int calculate_zcolor(int z) //Gradiant color
{
	if (z > 10)
		return 0xFF0000; // Rojo para alturas altas
	else if (z > 5)
		return 0x00FF00; // Verde para alturas medias
	else
		return 0x0000FF; // Azul para alturas bajas
}

int interpolate_color(int color1, int color2, double factor)
{
	int r = ((color1 >> 16) & 0xFF) + factor * (((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF));
	int g = ((color1 >> 8) & 0xFF) + factor * (((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF));
	int b = (color1 & 0xFF) + factor * ((color2 & 0xFF) - (color1 & 0xFF));

	return (r << 16 | g << 8 | b);
}

void draw_line(t_point2d p0, t_point2d p1, mlx_image_t *image)
{
    int dx = abs(p1.x - p0.x);
    int dy = abs(p1.y - p0.y);
    int sx = (p0.x < p1.x) ? 1 : -1;
    int sy = (p0.y < p1.y) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        // Verificar límites antes de dibujar
        if (p0.x >= 0 && p0.x < WIDTH && p0.y >= 0 && p0.y < HEIGHT)
        {
            mlx_put_pixel(image, p0.x, p0.y, 0xFFFFFF); // Usar un color fijo para depuración
        }

        if (p0.x == p1.x && p0.y == p1.y)
            break;

        e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            p0.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            p0.y += sy;
        }
    }
}

t_point2d project_point(t_point3d point3d, t_map *map)
{
    t_point2d point2d;

    // Calcular el factor de escala
    double scale_x = (double)WIDTH / (map->width + map->height);
    double scale_y = (double)HEIGHT / (map->width + map->height);
    double scale = fmin(scale_x, scale_y) * 0.8; // Ajusta el factor 0.8 según sea necesario

    // Calcular los desplazamientos para centrar el mapa
    int offset_x = WIDTH / 2 - ((map->width - map->height) * cos(0.523599) * scale) / 2;
    int offset_y = HEIGHT / 2 - ((map->width + map->height) * sin(0.523599) * scale) / 2;

    // Aplicar la proyección isométrica
    point2d.x = (point3d.x - point3d.y) * cos(0.523599) * scale + offset_x;
    point2d.y = (point3d.x + point3d.y) * sin(0.523599) * scale - point3d.z * scale + offset_y;
    point2d.z = point3d.z;
    point2d.rgba = point3d.mapcolor;

    // Depuración: Imprimir las coordenadas proyectadas
    ft_printf("Projected point: x=%d, y=%d, z=%d\n", point2d.x, point2d.y, point2d.z);

    return point2d;
}

void draw_map(t_fdf *fdf)
{
    int x, y;

    if (!fdf || !fdf->map || !fdf->map->values)
        handle_error("Invalid FDF or map structure");

    y = 0;
    while (y < fdf->map->height)
    {
        x = 0;
        while (x < fdf->map->width)
        {
            // Proyectar el punto actual
            t_point3d p0 = {x, y, fdf->map->values[y][x], 0xFFFFFF, calculate_zcolor(fdf->map->values[y][x])};
            t_point2d p2d_0 = project_point(p0, fdf->map);

            // Dibujar línea horizontal hacia el siguiente punto
            if (x < fdf->map->width - 1)
            {
                t_point3d p1 = {x + 1, y, fdf->map->values[y][x + 1], 0xFFFFFF, calculate_zcolor(fdf->map->values[y][x + 1])};
                t_point2d p2d_1 = project_point(p1, fdf->map);
                draw_line(p2d_0, p2d_1, fdf->image);
            }

            // Dibujar línea vertical hacia el punto inferior
            if (y < fdf->map->height - 1)
            {
                t_point3d p1 = {x, y + 1, fdf->map->values[y + 1][x], 0xFFFFFF, calculate_zcolor(fdf->map->values[y + 1][x])};
                t_point2d p2d_1 = project_point(p1, fdf->map);
                draw_line(p2d_0, p2d_1, fdf->image);
            }

            x++;
        }
        y++;
    }

    // Renderizar la imagen final
    mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
}
