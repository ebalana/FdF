/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:02:53 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/21 13:23:29 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/ultimate_libft/ultimate_libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# define WIDTH				1240
# define HEIGHT				800
# define FORMAT				"Wrong format -> ./fdf maps/filename.fdf"
# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"
# define FILE_ERROR			"Unable to open file"

/* 
typedef struct s_map
{
	int		width;
	int		height;
	int		**values;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
}				t_fdf;
*/

typedef struct s_map
{
	int			width;
	int			height;
	int			**values; // Valores del archivo
}				t_map;

typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
	int			mapcolor; // Color definido por el mapa (opcional)
	int			zcolor;   // Color calculado en base a la altura (opcional)
}				t_point3d;

typedef struct s_point2d
{
	int			x;
	int			y;
	int			z; // Puede ser útil para colores
	int			rgba; // Color en formato RGBA
}				t_point2d;

typedef struct s_fdf
{
	mlx_t			*mlx;
	t_map			*map;
	t_point3d		**points_3d; // Arreglo 2D de puntos 3D
	t_point2d		**points_2d; // Arreglo 2D de puntos proyectados
	mlx_image_t		*image;
}					t_fdf;

void	handle_error(const char *message);
void	cleanup_fdf(t_fdf *fdf);
void	free_split(char **split);
void	free_map(t_map *map);
void	close_window(void *param);
int		process_line(char *line, t_map *map);
int		is_valid_hex_color(char *str);
int		is_valid_number(char *str);
int		append_row_to_map(t_map *map, int *row);
int		process_trimmed_line(char *trimmed_line, t_map *map);
int		validate_and_convert_values(char **values, int width, int *row);
int		validate_row(char **values, int width, int **row);
char	**split_line_and_get_width(char *trimmed_line, int *width);
int		append_row_to_map_and_height(t_map *map, int *row);
int		process_trimmed_line(char *trimmed_line, t_map *map);


void	draw_map(t_fdf *fdf);


#endif