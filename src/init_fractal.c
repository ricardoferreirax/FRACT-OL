/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:17:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/08 00:31:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_graphics(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		return ;
	fractal->res_width = WIDTH;
	fractal->res_height = HEIGHT;

	fractal->win = mlx_new_window(fractal->mlx, fractal->res_width,
			fractal->res_height, "Fract-ol");
	if (!fractal->win)
		return ;
	fractal->img = mlx_new_image(fractal->mlx, fractal->res_width,
			fractal->res_height);
	if (!fractal->img)
		return ;
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	fractal->zoom = 1.0;
	fractal->offset_x = 0;
	fractal->offset_y = 0;
	fractal->max_iter = 50;
	fractal->color_scheme = 0;
}

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

void	init_fractal(t_fractal *fractal, int argc, char **argv)
{
	init_graphics(fractal);
	if (!fractal->mlx)
		return ;
	init_fractal_type(fractal, argc, argv);
}

int	validate_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr("Error: No fractal type provided\n");
		return (0);
	}
	if (!ft_strcmp(argv[1], "mandelbrot") && argc == 2)
		return (1);
	if (!ft_strcmp(argv[1], "julia") && argc == 4)
		return (1);
	if (!ft_strcmp(argv[1], "burning_ship") && argc == 2)
		return (1);
	ft_putstr("Error: Invalid arguments\n");
	return (0);
}
