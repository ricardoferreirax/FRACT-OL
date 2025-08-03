/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:35:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/03 19:38:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(double c_re, double c_im, int max_iter)
{
	double	z_re;
	double	z_im;
	double	tmp;
	int		iter;

	iter = 0;
	z_re = 0;
	z_im = 0;
	while ((z_re * z_re + z_im * z_im <= 4.0) && (iter < max_iter))
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		iter++;
	}
	return (iter);
}

void	draw_mandelbrot(t_fractal *fractal)
{
	int	x;
	int	y;
	int	iter;

	y = 0;
	while (y < fractal->res_height)
	{
		x = 0;
		while (x < fractal->res_width)
		{
			fractal->c_re = (x - fractal->res_width / 2.0) * (4.0 / fractal->res_width)
				/ fractal->zoom + fractal->offset_x;
			fractal->c_im = (y - fractal->res_height / 2.0) * (4.0 / fractal->res_height)
				/ fractal->zoom + fractal->offset_y;
			iter = mandelbrot(fractal->c_re, fractal->c_im, fractal->max_iter);
			my_mlx_pixel_put(&fractal->img, x, y,
				get_color(iter, fractal->max_iter, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img.img, 0, 0);
}