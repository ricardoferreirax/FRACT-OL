/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:23:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 17:02:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;
	int offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
	}
}

int	get_fractal_iterations(t_fractol *f, t_complex *p)
{
	int			nb_iter;
	t_complex	c;

	nb_iter = 0;
	c.re = p->re;
	c.im = p->im;
	if (!ft_strncmp(f->type, "mandelbrot", 10))
		nb_iter = mandelbrot(c, f->c_max_iter);
	else if (!ft_strncmp(f->type, "julia", 5))
	{
		c.re = f->julia_re;
		c.im = f->julia_im;
		nb_iter = julia(c, *p, f->c_max_iter);
	}
	else if (!ft_strncmp(f->type, "burningship", 11))
		nb_iter = burning_ship(c, f->c_max_iter);
	else if (!ft_strncmp(f->type, "phoenix", 7))
		nb_iter = phoenix(c, f->pv.p, f->pv.c, f->c_max_iter);
	return (nb_iter);
}

void	render_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			nb_iter;
	t_complex	p;
	int			color;

	if (f->img.img)
		mlx_destroy_image(f->mlx, f->img.img);
	init_image(f);
	y = -1;
	while (++y < WIDTH)
	{
		x = -1;
		while (++x < HEIGHT)
		{
			p.re = scale(x, -2.0 * f->zoom + f->offset_x, 2.0 * f->zoom
					+ f->offset_x, WIDTH);
			p.im = scale(y, -2.0 * f->zoom + f->offset_y, 2.0 * f->zoom
					+ f->offset_y, HEIGHT);
			nb_iter = get_fractal_iterations(f, &p);
			color = colorize(nb_iter, f);
			my_mlx_pixel_put(&f->img, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
}
