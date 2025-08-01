/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:34:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 12:39:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	julia(t_fractal *fractal, double z_re, double z_im, int max_iter)
{
	double	tmp;
	double	c_re;
	double	c_im;
	int		iter;

	c_re = fractal->c_re;
	c_im = fractal->c_im;
	iter = 0;
	while (iter < max_iter)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		if ((z_re * z_re + z_im * z_im) > 4.0)
			break ;
		iter++;
	}
	return (iter);
}

void	draw_julia(t_fractal *fractal)
{
	double	z_re;
	double	z_im;
	int		x;
	int		y;
	int		iter;

	x = 0;
	y = 0;
	while (y < fractal->res_height)
	{
		x = 0;
		while (x < fractal->res_width)
		{
			z_re = 1.5 * (x - fractal->res_width / 2)
				/ (0.5 * fractal->zoom * fractal->res_width) + fractal->offset_x;
			z_im = (y - fractal->res_height / 2)
				/ (0.5 * fractal->zoom * fractal->res_height) + fractal->offset_y;
			iter = julia(fractal, zr, zi, fractal->max_iter);
			my_mlx_pixel_put(&fractal->img, x, y,
				get_color(iter, fractal->max_iter, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img.img, 0, 0);
}