/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:22 by ebalana-          #+#    #+#             */
/*   Updated: 2025/01/20 17:31:16 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	cleanup_fdf(t_fdf *fdf)
{
	if (fdf->image)
		mlx_delete_image(fdf->mlx, fdf->image);
	if (fdf->mlx)
		mlx_close_window(fdf->mlx);
	if (fdf->map)
		free_map(fdf->map);
}

void	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_close_window(fdf->mlx);
	cleanup_fdf(fdf);
	exit(0);
}

void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}
