/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:11:55 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/28 17:11:10 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_hex_color(char *str)
{
	int	i;

	if (ft_strlen(str) < 3 || str[0] != '0' || str[1] != 'x')
		return (0);
	i = 2;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'A' && str[i] <= 'F') \
		|| (str[i] >= 'a' && str[i] <= 'f')))
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_convert_values(char **values, int width, int *row)
{
	char	*value;
	char	*comma_pos;
	char	*number;
	char	*color;
	int		i;

	i = -1;
	while (++i < width)
	{
		value = values[i];
		comma_pos = ft_strchr(value, ',');
		if (comma_pos)
		{
			*comma_pos = '\0';
			number = value;
			color = comma_pos + 1;
			if (!is_valid_number(number) || !is_valid_hex_color(color))
				return (0);
			row[i] = ft_atoi(number);
		}
		else if (!is_valid_number(value))
			return (0);
		row[i] = ft_atoi(value);
	}
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
