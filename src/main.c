/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:23:14 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/30 16:45:27 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	all_hooks(void *param)
{
	t_fdf	*fdf;
	int		needs_redraw;

	fdf = (t_fdf *)param;
	needs_redraw = 0;
	if (ft_hook(param) || ft_rotations(param))
	{
		needs_redraw = 1;
	}
	if (needs_redraw)
	{
		mlx_delete_image(fdf->mlx, fdf->image);
		fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
		draw_map(fdf);
		needs_redraw = 0;
	}
}

int	main(int ac, char *av[])
{
	t_fdf	*fdf;

	if (ac != 2)
		handle_error(FORMAT);
	fdf = init_fdf(av[1]);
	draw_map(fdf);
	mlx_loop_hook(fdf->mlx, all_hooks, fdf);
	mlx_close_hook(fdf->mlx, close_window, fdf);
	mlx_loop(fdf->mlx);
	cleanup_fdf(fdf);
	return (0);
}
