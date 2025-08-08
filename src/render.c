/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:23:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/08 18:51:44 by rmedeiro         ###   ########.fr       */
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
	if (ft_strcmp(f->type, "mandelbrot") == 0)
		nb_iter = mandelbrot(c, f->c_max_iter);
	else if (ft_strcmp(f->type, "julia") == 0)
	{
		c.re = f->julia_re;
		c.im = f->julia_im;
		nb_iter = julia(c, *p, f->c_max_iter);
	}
	else if (ft_strcmp(f->type, "burningship") == 0)
		nb_iter = burning_ship(c, f->c_max_iter);
	else if (ft_strcmp(f->type, "phoenix") == 0)
		nb_iter = phoenix(c, f->pv.p, f->pv.c, f->c_max_iter);
	return (nb_iter);
}

t_complex	ft_mapping(int x, int y, t_fractol *f)
{
	t_complex	c_point;

	c_point.re = scale(x, -2.0 * f->zoom + f->offset_x, 2.0 * f->zoom + f->offset_x, WIDTH);
	c_point.im = scale(y, -2.0 * f->zoom + f->offset_y, 2.0 * f->zoom + f->offset_y, HEIGHT);
	return (c_point);
}

void	render_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			nb_iter;
	t_complex	c_point;
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
			nb_iter = get_fractal_iterations(f, &c_point);
			color = colorize(nb_iter, f);
			my_mlx_pixel_put(&f->img, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
}
