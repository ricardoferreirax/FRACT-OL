/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:23:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 19:13:58 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
	}
}

int	fractal_escape_time(t_fractol *f, t_cpx *c_point)
{
	t_cpx	c;
	int		nb_iter;

	nb_iter = 0;
	c.re = c_point->re;
	c.im = c_point->im;
	if (ft_strcmp(f->type, "mandelbrot") == 0)
		nb_iter = mandelbrot(c, f->c_max_iter);
	else if (ft_strcmp(f->type, "julia") == 0)
	{
		c.re = f->julia_re;
		c.im = f->julia_im;
		nb_iter = julia(c, *c_point, f->c_max_iter);
	}
	else if (ft_strcmp(f->type, "burningship") == 0)
		nb_iter = burning_ship(c, f->c_max_iter);
	return (nb_iter);
}

void	render_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			nb_iter;
	t_cpx		c_point;
	int			color;

	if (f->img.img)
		mlx_destroy_image(f->mlx, f->img.img);
	init_image(f);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c_point = ft_mapping(x, y, f);
			nb_iter = fractal_escape_time(f, &c_point);
			color = colorize(nb_iter, f);
			my_mlx_pixel_put(&f->img, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
}
