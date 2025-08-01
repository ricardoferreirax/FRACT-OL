/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:48:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 15:50:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	exit_fractol(t_fractal *fractal, int errno)
{
	if (fractal->img)
		mlx_destroy_image(img->mlx, img->img);
	if (fractal->mlx_win)
		mlx_destroy_window(img->mlx, img->mlx_win);
	if (fractal->mlx)
	{
		free(fractal->mlx);
		fractal->mlx = NULL;
	}
	if (fractal)
	{
		free(fractal);
		fractal = NULL;
	}
	exit(errno);
	return (0);
}

int	ft_error(t_fractal *fractal, int errno)
{
	perror("fractol: ");
	exit_fractol(fractal, errno);
	return (0);
}
