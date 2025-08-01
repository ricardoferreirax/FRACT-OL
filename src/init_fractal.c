/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:17:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 15:51:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_fractal_type(t_fractal *fractal, int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "mandelbrot"))
		fractal->type = 1;
	else if (!ft_strcmp(argv[1], "julia") && argc == 4)
	{
		fractal->type = 2;
		fractal->julia_re = ft_atof(argv[2]);
		fractal->julia_im = ft_atof(argv[3]);
	}
	else if (!ft_strcmp(argv[1], "burning_ship") && argc == 2)
	{
		fractal->type = 3;
	}
	else
	{
		ft_putstr("Error: Invalid fractal type or parameters\n");
		print_usage();
		exit(1);
	}
}


t_fractal	*init_fractol(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		ft_error(fractal, 1);
	fractal->mlx_win = mlx_new_window(fractal->mlx, 
        fractal->res_width, fractal->res_height, "Fract-ol");
	if (fractal->mlx_win == NULL)
		ft_error(fractal, 1);
	fractal->img = mlx_new_image(fractal->mlx, fractal->res_width,
			fractal->res_height);
	if (fractal->img == NULL)
		ft_error(img, 1);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	img->x = 0;
	img->y = 0;
	img->color = 0x0006b1;
	img->zoom = 300;
	img->off_x = -2.178;
	img->off_y = -1.512;
	img->iterations = 50;
	return (img);
}
