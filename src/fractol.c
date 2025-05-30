/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/30 11:49:39 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
/*
void	init_fractal(t_fractal *fractal, char *name)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		return ;
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fract-ol");
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	fractal->zoom = 1.0;
	fractal->offset_x = 0;
	fractal->offset_y = 0;
	fractal->max_iter = 50;
	if (!ft_strcmp(name, "mandelbrot"))
		fractal->type = 1;
	else if (!ft_strcmp(name, "julia"))
	{
		fractal->type = 2;
		fractal->julia_re = -0.7;
		fractal->julia_im = 0.27015;
	}
	else if (!ft_strcmp(name, "burning_ship"))
		fractal->type = 3;
	else
	{
		free_fractal(fractal);
		exit(ft_printf("Usage: ./fractol mandelbrot | julia | burning_ship\n"));
	}
}*/

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	if (argc != 2)
		return (ft_putstr("Usage: ./fractol <fractal_name>\n"), 1);
	init_fractal(&fractal, argv[1]);
	if (!fractal.mlx)
		return (1);
	render_fractal(&fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_mouse_hook(fractal.win, handle_mouse, &fractal);
	mlx_hook(fractal.win, 17, 0, close_win, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}