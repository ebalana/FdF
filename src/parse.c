/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:25 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 17:03:00 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	append_row_to_map(t_map *map, int *row)
{
	int	**new_values;
	int	i;

	new_values = malloc(sizeof(int *) * (map->height + 1));
	if (!new_values)
		return (0);
	i = 0;
	while (i < map->height)
	{
		new_values[i] = map->values[i];
		i++;
	}
	new_values[map->height] = row;
	free(map->values);
	map->values = new_values;
	return (1);
}

char	**split_line_and_get_width(char *trimmed_line, int *width)
{
	char	**values;

	values = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!values)
		return (NULL);
	*width = 0;
	while (values[*width])
		(*width)++;
	return (values);
}

int	append_row_to_map_and_height(t_map *map, int *row)
{
	if (!append_row_to_map(map, row))
	{
		free(row);
		return (0);
	}
	map->height++;
	return (1);
}

int	process_trimmed_line(char *trimmed_line, t_map *map)
{
	char	**values;
	int		*row;
	int		width;

	values = split_line_and_get_width(trimmed_line, &width);
	if (!values)
		return (0);
	if (map->height == 0)
		map->width = width;
	if (map->width != width)
	{
		free_split(values);
		return (0);
	}
	if (!validate_row(values, width, &row))
	{
		free_split(values);
		return (0);
	}
	if (!append_row_to_map_and_height(map, row))
	{
		free_split(values);
		return (0);
	}
	return (1);
}

int	process_line(char *line, t_map *map)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\r");
	if (!trimmed_line || ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return (0);
	}
	if (!process_trimmed_line(trimmed_line, map))
		return (0);
	return (1);
}
