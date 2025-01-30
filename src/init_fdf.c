/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:13:10 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 16:43:32 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	check_file_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".fdf", 4) != 0)
		handle_error(WRONG_EXTENSION);
}

t_map	*initialize_map(int fd)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		handle_error(MALLOC);
	}
	map->width = 0;
	map->height = 0;
	map->z_max = 0;
	map->z_min = 0;
	map->values = NULL;
	map->scale = 1.0;
	map->offset_x = WIDTH / 2;
	map->offset_y = HEIGHT / 2;
	map->elevation = 1.0;
	map->alpha = 0.0;
	map->zoom = 1.0;
	map->flat_mode = 0;
	return (map);
}

t_map	*parse_input(char *filename)
{
	int		fd;
	char	*line;
	t_map	*map;

	check_file_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(FILE_ERROR);
	map = initialize_map(fd);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_line(line, map))
		{
			free_map(map);
			free(line);
			close(fd);
			handle_error(INVALID_MAP);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

t_fdf	*init_fdf(char *filename)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		handle_error(MALLOC);
	fdf->map = parse_input(filename);
	if (!fdf->map)
	{
		free(fdf);
		handle_error(INVALID_MAP);
	}
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF ebalana-", true);
	if (!fdf->mlx)
	{
		cleanup_fdf(fdf);
		handle_error(MLX_FAIL);
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		cleanup_fdf(fdf);
		handle_error(MLX_IMAGE);
	}
	return (fdf);
}
