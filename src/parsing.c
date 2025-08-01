/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:01:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 12:20:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	print_usage(void)
{
    ft_putstr_fd("\n\033[31;1mWRONG INPUT FORMAT\n\n", 1);
    ft_putstr_fd("\033[33mInput Format: ./fractol", 1);
	ft_putstr("<fractal_type> <params>\n\n");
	ft_putstr("Fractal types: Mandelbrot, Burning_ship and Julia");
	ft_putstr("  julia <c_real> <c_imag>\n");
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
    ft_putstr_fd("\033[36mCommands:\n", 1);
	ft_putstr_fd("\texit                 : Press esc\n", 1);
	ft_putstr_fd("\tmove                 : ← ↑ → ↓ or left mouse click\n", 1);
	ft_putstr_fd("\tzoom                 : mouse scroll\n", 1);
	ft_putstr_fd("\tcolor change         : press A or D\n", 1);
	ft_putstr_fd("\n\n\033[0m", 1);
    exit(EXIT_FAILURE);
}

void	check_arguments(t_fractal *fractal, int ac, char **av)
{
	if (ac < 4)
		error_function();
	fractal->cr = atof(av[2]);
	fractal->ci = atof(av[3]);
	if (fractal->cr < -2.0 || fractal->cr > 2.0
		|| fractal->ci < -2.0 || fractal->ci > 2.0)
		error_function();
}

void	ft_parse(t_fractal *fractal, int ac, char **av)
{
	char	*name;

	name = av[1];
	if (!name)
		error_function();
    if (ac < 2)
	{
		ft_putstr("Error: No fractal type provided\n");
		return (0);
	}
	if (ft_strncmp(name, "mandelbrot", 11) == 0 && ac == 2)
		fractal->type = 0;
	else if (ft_strncmp(name, "julia", 6) == 0)
	{
		check_arguments(fractal, ac, av);
		fractal->type = 1;
	}
	else if (ft_strncmp(name, "burning_ship", 13) == 0 && ac == 2)
		fractal->type = 2;
	else
		error_function();
}
