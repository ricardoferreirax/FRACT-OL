/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 08:45:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/08 09:14:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	interpolation(double i, double min, double max, int max_iter)
{
	return (min + (max - min) * (i / (double)max_iter));
}

void	normalize_color_scheme(t_fractal *fractal)
{
	if (fractal->color_scheme < 0)
		fractal->color_scheme += 5;
	else if (fractal->color_scheme >= 5)
		fractal->color_scheme %= 5;
}
