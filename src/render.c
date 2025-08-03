/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:23:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/03 19:26:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	put_pixel(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * fractal->line_length) + (x * (fractal->bpp / 8));
		dst = fractal->addr + offset;
		*(unsigned int *)dst = color;
	}
}

t_complex	compute_complex(int x, int y, t_fractal *fractal)
{
	t_complex	c;
	double		scale_x;
	double		scale_y;

	scale_x = (4.0 / fractal->res_width) * fractal->zoom;
	scale_y = (4.0 / fractal->res_height) * fractal->zoom;
	c.re = (x - fractal->res_width / 2) * scale_x + fractal->offset_x;
	c.im = (y - fractal->res_height / 2) * scale_y + fractal->offset_y;
	return (c);
}

int	compute_iteration(t_complex c, t_fractal *fractal)
{
	t_complex	julia_c;

	if (fractal->type == 1)
		return (mandelbrot(c, fractal->max_iter));
	else if (fractal->type == 2)
	{
		julia_c.re = fractal->julia_re;
		julia_c.im = fractal->julia_im;
		return (julia(c, julia_c, fractal->max_iter));
	}
	else if (fractal->type == 3)
		return (burning_ship(c, fractal->max_iter));
	return (0);
}

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->type == 1)
		draw_mandelbrot(fractal);
	else if (fractal->type == 2)
		draw_julia(fractal);
	else if (fractal->type == 3)
		draw_burning_ship(fractal);
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
