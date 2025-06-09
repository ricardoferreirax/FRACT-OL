/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/09 09:44:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	coloring(double i, t_fractal *fractal)
{
	if (fractal->color_scheme == 0)
		return (color_rainbow(i, fractal->max_iter));
	else if (fractal->color_scheme == 1)
		return (bernstein_polynomials(i, 0, fractal->max_iter));
	else if (fractal->color_scheme == 2)
		return (bernstein_polynomials(i, 1, fractal->max_iter));
	else if (fractal->color_scheme == 3)
		return (cosine_coloring(i, 0, fractal->max_iter));
	else
		return (cosine_coloring(i, 1, fractal->max_iter));
}

int	bernstein_polynomials(double i, int version, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = i / max_iter;
	if (version == 0)
	{
		r = (int)(9 * (1 - t) * pow(t, 3) * 255);
		g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		b = (int)(8.5 * (1 - t) * (0.75 - t) * (1 - t) * t * 200);
	}
	else
	{
		r = (int)(9 * pow((1 - t), 3) * t * 255);
		g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		b = (int)(8.5 * (1 - t) * pow(t, 3) * 255);
	}
	return ((r << 16) | (g << 8) | b);
}

int	cosine_coloring(double i, int version, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = i / max_iter;
	if (version == 0)
	{
		r = (int)(255 * (0.5 + 0.5 * cos(PI2 * (t + 0.00))));
		g = (int)(255 * (0.5 + 0.5 * cos(PI2 * (t + 0.33))));
		b = (int)(255 * (0.5 + 0.5 * cos(PI2 * (t + 0.66))));
	}
	else
	{
		r = (int)(200 * (0.5 + 0.5 * cos(PI2 * (t + 0.65))));
		g = (int)(100 * (0.5 + 0.5 * cos(PI2 * (t + 0.4))));
		b = (int)(150 * (0.5 - 0.5 * cos(PI2 * (t + 0.5))));
	}
	return ((r << 16) | (g << 8) | b);
}

int	color_rainbow(double i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = i / max_iter;
	r = (int)(sin(6.28318 * t + 0) * 127.5 + 127.5);
	g = (int)(sin(6.28318 * t + 2.09439) * 127.5 + 127.5);
	b = (int)(sin(6.28318 * t + 4.18878) * 127.5 + 127.5);
	return (r << 16 | g << 8 | b);
}

int	get_colors(double i, t_fractal *fractal)
{
	if (i == fractal->max_iter)
		return (0x000000);
	return (coloring(i, fractal));
}
