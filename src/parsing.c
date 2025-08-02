/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:34:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/02 12:00:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	validate_args(int ac, char **av)
{
	if (!ft_strcmp(av[1], "mandelbrot") && ac == 2)
		return (1);
	else if (!ft_strcmp(av[1], "julia") && ac == 4)
		return (1);
	else if (!ft_strcmp(av[1], "burning_ship") && ac == 2)
		return (1);
    else
        error_function();
}

void	check_arguments(t_fractal *fractal, int ac, char **av)
{
	if (ac < 4)
		error_function();
	fractal->julia_re = atof(av[2]);
	fractal->julia_im = atof(av[3]);
	if (fractal->c_re < -2.0 || fractal->c_re > 2.0
		|| fractal->c_im < -2.0 || fractal->c_im > 2.0)
		error_function();
}

void	ft_parse_args(t_fractal *fractal, int ac, char **av)
{
    if (!av[1])
        error_function();
    if (ac < 2 || ac > 4)
        error_function();
	if (ft_strcmp(av[1], "mandelbrot") == 0 && ac == 2)
		fractal->type = 1;
	else if (ft_strcmp(av[1], "julia") == 0 && ac == 4)
	{
        ft_check_arguments(fractal, ac, av)
		fractal->type = 2;
	}
	else if (ft_strcmp(argv[1], "burning_ship") == 0 && argc == 2)
		fractal->type = 3;
	else
		error_function();
}
