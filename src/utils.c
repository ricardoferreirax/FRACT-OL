/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:24:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/07 20:29:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_colors(int iteration, t_fractal *fractal)
{
	double	t;

	if (!fractal)
		return (0x000000);
	if (iteration == fractal->max_iter)
		return (0x000000);
	t = (double)iteration / fractal->max_iter;
	if (fractal->color_scheme == 0)
		return (color_blue_violet(t));
	else if (fractal->color_scheme == 1)
		return (color_red_yellow(t));
	else if (fractal->color_scheme == 2)
		return (color_blue_gradient(t));
	else if (fractal->color_scheme == 3)
		return (color_green_turquoise(t));
	else if (fractal->color_scheme == 4)
		return (color_pink_white(t));
	return (color_rainbow(iteration));
}

void	free_fractal(t_fractal *fractal)
{
	if (!fractal)
		return ;
	if (fractal->img)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win)
		mlx_destroy_window(fractal->mlx, fractal->win);
	if (fractal->mlx)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
	}
}

int	color_rainbow(int iteration)
{
	int	r;
	int	g;
	int	b;

	r = (int)(sin(0.16 * iteration + 4) * 127 + 128);
	g = (int)(sin(0.16 * iteration + 2) * 127 + 128);
	b = (int)(sin(0.16 * iteration) * 127 + 128);
	return (r << 16 | g << 8 | b);
}

