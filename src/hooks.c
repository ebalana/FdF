/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:36:45 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/28 17:38:31 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	handle_prespectives_keys(t_fdf *fdf)
{
	int	needs_redraw;

	needs_redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
	{
		fdf->map->alpha = 0.78;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
	{
		fdf->map->alpha = 1.57;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_T))
	{
		fdf->map->alpha = 0.8;
		needs_redraw = 1;
	}
	return (needs_redraw);
}

int	handle_movement_keys(t_fdf *fdf)
{
	int	needs_redraw;

	needs_redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	{
		fdf->map->offset_y -= 5;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
	{
		fdf->map->offset_y += 5;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
	{
		fdf->map->offset_x -= 5;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
	{
		fdf->map->offset_x += 5;
		needs_redraw = 1;
	}
	return (needs_redraw);
}

int	handle_zoom_and_flat_keys(t_fdf *fdf)
{
	int	needs_redraw;

	needs_redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
	{
		fdf->map->zoom += 0.075;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
	{
		fdf->map->zoom -= 0.075;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
	{
		fdf->map->flat_mode = 1;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		fdf->map->flat_mode = -1;
		needs_redraw = 1;
	}
	return (needs_redraw);
}

int	ft_hook(void *param)
{
	t_fdf	*fdf;
	int		needs_redraw;

	fdf = (t_fdf *)param;
	needs_redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
	{
		fdf->map->elevation += 0.1;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
	{
		fdf->map->elevation -= 0.1;
		needs_redraw = 1;
	}
	needs_redraw |= handle_movement_keys(fdf);
	needs_redraw |= handle_zoom_and_flat_keys(fdf);
	return (needs_redraw);
}

int	ft_rotations(void *param)
{
	t_fdf	*fdf;
	int		needs_redraw;

	fdf = (t_fdf *)param;
	needs_redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
	{
		fdf->map->alpha += 0.02;
		needs_redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
	{
		fdf->map->alpha -= 0.02;
		needs_redraw = 1;
	}
	needs_redraw |= handle_prespectives_keys(fdf);
	return (needs_redraw);
}
