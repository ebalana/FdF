/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:25 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/22 12:08:27 by ebalana-         ###   ########.fr       */
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

int	validate_row(char **values, int width, int **row)
{
	*row = malloc(sizeof(int) * width);
	if (!*row)
	{
		free_split(values);
		return (0);
	}
	if (!validate_and_convert_values(values, width, *row))
	{
		free_split(values);
		free(*row);
		return (0);
	}
	free_split(values);
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
		return (0);
	if (!validate_row(values, width, &row))
		return (0);
	if (!append_row_to_map_and_height(map, row))
		return (0);
	return (1);
}

/* int process_line(char *line, t_map *map)
{
	char	**values;
	int	 *row;
	int	 width;
	int	 i;
	char	*trimmed_line;
		
	// Eliminar espacios al principio y final de la línea
	trimmed_line = ft_strtrim(line, " \n\r");
	if (!trimmed_line || ft_strlen(trimmed_line) == 0) {
		free(trimmed_line);
		ft_printf("Línea vacía o solo espacios\n");
		return (0); // Línea vacía o solo espacios
	}
	// Divide la línea en elementos separados por espacios
	values = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!values)
		return (0);
	// Calcular el ancho de la fila
	width = 0;
	while (values[width])
		width++;
	ft_printf("Ancho de la línea: %d\n", width);
	// Si es la primera línea, establece el ancho del mapa
	if (map->height == 0)
		map->width = width;
	// Verifica que las líneas tengan la misma cantidad de elementos
	if (map->width != width) {
		free_split(values);
		ft_printf("Error: Las filas no tienen el mismo número de elementos\n");
		return (0); // Error: las filas no tienen el mismo número de elementos
	}
	// Reserva memoria para la fila actual
	row = malloc(sizeof(int) * width);
	if (!row) {
		free_split(values);
		return (0); // Error de memoria
	}
	// Convierte los valores a enteros y procesa los colores opcionales
	i = 0;
	while (i < width) {
		char *value = values[i];
		char *comma_pos = ft_strchr(value, ','); // Busca la coma

		if (comma_pos) {
			// Separar el número y el color
			*comma_pos = '\0'; // Divide la cadena en dos partes
			char *number_part = value;
			char *color_part = comma_pos + 1;

			// Validar número
			if (!is_valid_number(number_part)) {
				ft_printf("Error: Número no válido en: '%s'\n", number_part);
				free_split(values);
				free(row);
				return (0);
			}

			// Validar color hexadecimal
			if (!is_valid_hex_color(color_part)) {
				ft_printf("Error: Color hexadecimal no válido en: '%s'\n", color_part);
				free_split(values);
				free(row);
				return (0);
			}

			// Convertir valores
			row[i] = ft_atoi(number_part); // Guardamos solo el número en este caso
			ft_printf("Número: %d, Color: %s\n", row[i], color_part);
		} else {
			// Validar y convertir si no hay color
			if (!is_valid_number(value)) {
				ft_printf("Error: Número no válido en: '%s'\n", value);
				free_split(values);
				free(row);
				return (0);
			}
			row[i] = ft_atoi(value);
			ft_printf("Número: %d\n", row[i]);
		}

		i++;
	}
	free_split(values);
	// Almacena la fila en el mapa
	if (!append_row_to_map(map, row)) {
		free(row);
		ft_printf("Error al agregar la fila\n");
		return (0); // Error al agregar la fila
	}
	map->height++;
	ft_printf("Fila agregada correctamente. Altura actual del mapa: %d\n", map->height);
	return (1); // Éxito
} */