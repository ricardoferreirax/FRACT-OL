/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/07 20:55:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

void print_usage(void)
{
	printf("Usage: ./fractol <fractal_type> [params]\n");
	printf("Fractal types:\n");
	printf("  mandelbrot\n");
	printf("  julia <c_real> <c_imag>\n");
	printf("  phoenix <c_real> <c_imag> <p>\n");
	printf("Examples:\n");
	printf("  ./fractol mandelbrot\n");
	printf("  ./fractol julia -0.4 0.6\n");
	printf("  ./fractol phoenix -0.4 0.6 -0.5\n");
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (!validate_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	ft_memset(&fractal, 0, sizeof(t_fractal));
	init_fractal(&fractal, argc, argv);
	if (!fractal.mlx)
		return (1);
	render_fractal(&fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_mouse_hook(fractal.win, handle_mouse, &fractal);
	mlx_hook(fractal.win, 17, 0, close_win, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
