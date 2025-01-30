/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:02:53 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 16:44:03 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/ultimate_libft/ultimate_libft.h"
# include <math.h>
# include <stdlib.h>
# include <errno.h>

# define WIDTH				1920
# define HEIGHT				1080
# define FORMAT				"Wrong format -> ./fdf maps/filename.fdf"
# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"
# define WRONG_EXTENSION	"Wrong extension"
# define MLX_FAIL			"MLX initialization failed"
# define MLX_IMAGE			"Window creation failed"
# define FILE_ERROR			"Unable to open file"

typedef struct s_map
{
	int			width;
	int			height;
	int			z_max;
	int			z_min;
	int			**values;
	float		scale;
	int			offset_x;
	int			offset_y;
	float		elevation;
	float		alpha;
	float		zoom;
	int			flat_mode;
}				t_map;

typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
}				t_point3d;

typedef struct s_point2d
{
	int			x;
	int			y;
	int			z;
	int			rgba;
}				t_point2d;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
}				t_line;

typedef struct s_fdf
{
	mlx_t			*mlx;
	t_map			*map;
	t_point3d		**points_3d;
	t_point2d		**points_2d;
	mlx_image_t		*image;
}					t_fdf;

//main.c
int			main(int ac, char *av[]);
void		all_hooks(void *param);

//errors.c
void		handle_error(const char *message);
void		close_window(void *param);
void		cleanup_fdf(t_fdf *fdf);

//free.c
void		free_split(char **split);
void		free_map(t_map *map);

//init.fd
t_fdf		*init_fdf(char *filename);
t_map		*parse_input(char *filename);
t_map		*initialize_map(int fd);

//parse.c
int			process_line(char *line, t_map *map);
int			process_trimmed_line(char *trimmed_line, t_map *map);
int			append_row_to_map_and_height(t_map *map, int *row);
char		**split_line_and_get_width(char *trimmed_line, int *width);
int			append_row_to_map(t_map *map, int *row);

//validate.c
int			validate_row(char **values, int width, int **row);
int			validate_and_convert_values(char **values, int width, int *row);
int			is_valid_hex_color(char *str);
int			is_valid_number(char *str);

//map.c
t_point3d	rotate_z(t_point3d point3d, double alpha);
void		calculate_min_max_heights(t_map *map);
void		draw_connections(t_fdf *fdf, int x, int y, t_point2d p2d_0);
void		draw_map(t_fdf *fdf);

//project.c
double		get_scale(t_map *map);
t_point2d	project_flat(t_point3d point3d, double scale, t_map *map);
t_point2d	project_iso(t_point3d point3d, double scale, t_map *map);
t_point2d	project_point(t_point3d point3d, t_map *map);

//color.c
void		set_low_color(double h, int *r, int *g, int *b);
void		set_mid_low_color(double h, int *r, int *g, int *b);
void		set_mid_high_color(double h, int *r, int *g, int *b);
int			calculate_color(double normalized_height);

//draw_line.c
void		draw_line(t_point2d p0, t_point2d p1, mlx_image_t *image);
void		check_line(t_point2d p0, t_point2d p1, t_line *line);
void		pline(t_point2d p0, t_point2d p1, mlx_image_t *img, t_line *line);

//hooks.c
int			ft_hook(void *param);
int			ft_rotations(void *param);
int			handle_movement_keys(t_fdf *fdf);
int			handle_zoom_and_flat_keys(t_fdf *fdf);
int			handle_prespectives_keys(t_fdf *fdf);

#endif