/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/02 12:03:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

void	print_usage(void)
{
	ft_putstr("Usage: ./fractol <fractal_type> [params]\n");
	ft_putstr("Fractal types:\n");
	ft_putstr("  mandelbrot\n");
	ft_putstr("  julia <c_real> <c_imag>\n");
	ft_putstr("  burning_ship\n");
	ft_putstr("Examples:\n");
	ft_putstr("  ./fractol mandelbrot\n");
	ft_putstr("  ./fractol burning_ship\n");
	ft_putstr("  ./fractol julia -0.4 0.6\n");
	ft_putstr("  ./fractol julia 0.355 0.355\n");
	ft_putstr("  ./fractol julia -0.70176 -0.3842\n");
	ft_putstr("  ./fractol julia 0.285 0.013\n");
	ft_putstr("  ./fractol julia -0.8 0.156\n");
	ft_putstr("  ./fractol julia 0.37 -0.1\n");
	ft_putstr("  ./fractol julia -0.7269 0.1889\n");
	ft_putstr("  ./fractol julia -0.835 -0.2321\n");
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	ft_parse_args(&fractal, ac, av);
	ft_memset(&fractal, 0, sizeof(t_fractal));
	init_fractal(&fractal, ac, av);
	if (!fractal.mlx)
		return (1);
	render_fractal(&fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_mouse_hook(fractal.win, handle_mouse, &fractal);
	mlx_hook(fractal.win, 17, 0, close_win, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
