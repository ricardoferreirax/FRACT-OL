/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:38:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/02 11:38:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
