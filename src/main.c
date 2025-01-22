/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:23:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/22 12:07:37 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_map	*initialize_map_and_open_file(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(FILE_ERROR);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		handle_error(MALLOC);
	}
	map->width = 0;
	map->height = 0;
	map->values = NULL;
	return (map);
}

int	process_line(char *line, t_map *map)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\r");
	if (!trimmed_line || ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		ft_printf("Línea vacía o solo espacios\n");
		return (0);
	}
	if (!process_trimmed_line(trimmed_line, map))
		return (0);
	//ft_printf("Altura actual del mapa: %d\n", map->height);
	return (1);
}

t_map	*parse_input(char *filename)
{
	int		fd;
	char	*line;
	t_map	*map;

	map = initialize_map_and_open_file(filename);
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
	ft_printf("---------------------------\n DIMENSIONS \nWidth: %d\nHeight: %d\n", map->width, map->height);
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
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
	{
		cleanup_fdf(fdf);
		handle_error(mlx_strerror(mlx_errno));
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		cleanup_fdf(fdf);
		handle_error(mlx_strerror(mlx_errno));
	}
	return (fdf);
}

int	main(int ac, char *av[])
{
	t_fdf	*fdf;

	if (ac != 2)
		handle_error(FORMAT);
	fdf = init_fdf(av[1]);
	ft_printf("---------------------------\n");
	draw_map(fdf);

	mlx_close_hook(fdf->mlx, close_window, fdf);
	mlx_loop(fdf->mlx);
	cleanup_fdf(fdf);
	return (0);
}
