/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:01:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 15:18:07 by rmedeiro         ###   ########.fr       */
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

void	error_function(void)
{
	write(STDOUT_FILENO, "Use: ./fractol <fractal_name> [julia_params]", 47);
	write(STDOUT_FILENO, "\nAvailable fractals:\n", 22);
	write(STDOUT_FILENO, "  mandelbrot\n", 13);
	write(STDOUT_FILENO, "  burning_ship\n", 15);
	write(STDOUT_FILENO, "  julia <r> <i> (between -2.0 and 2.0)\n", 40);
	write(STDOUT_FILENO, "    Example: ./fractol julia 0.285 0.01\n", 39);
	exit(EXIT_FAILURE);
}

void	check_arguments(t_fractal *fractal, int ac, char **av)
{
	if (ac < 4)
		error_function();
	fractal->c_re = atof(av[2]);
	fractal->c_im = atof(av[3]);
	if (fractal->c_re < -2.0 || fractal->c_re > 2.0
		|| fractal->c_im < -2.0 || fractal->c_im > 2.0)
		error_function();
}

void	ft_parse(t_fractal *fractal, int ac, char **av)
{
	char	*name;

	name = av[1];
	if (!name)
		error_function();
    if (ac < 2)
		error_function()
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

/* void	check_args(int ac, char **av)
{
	if (ac < 2 || ac > 4)
	{
		ft_putstr("Error ! Invalid arguments\n");
		ft_putstr("Use: ./fractol [mandelbrot, julia, ship]\n");
		exit(1);
	}
	if (ft_strcmp(argv[1], "mandelbrot") != 0 
        && ft_strcmp(argv[1], "julia") != 0 
        && ft_strcmp(argv[1], "ship") != 0)
	{
		ft_putstr("Error ! Invalid fractal\n");
		ft_putstr("Use: ./fractol [mandelbrot, julia, ship]\n");
		exit(1);
	}
	if (ft_strcmp(argv[1], "julia") != 0 && argc != 2)
	{
		ft_printf("Error ! Invalid arguments\n");
		ft_printf("Use: ./fractol [mandelbrot, julia, ship]\n");
		exit(1);
	}
	if (ft_strcmp(argv[1], "julia") == 0 
        && (argc != 4 && argc != 2))
	{
		ft_printf("Error ! Invalid julia arguments\n");
		ft_printf("Use: ./fractol julia <c_real> <c_imag>\n");
		exit(1);
	}
} */