/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 08:45:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 19:42:29 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	polynomial_gradient(int iter, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(9.0 * (1 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1 - t) * (1 - t) * t * t * 255.0);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255.0);
	return ((r << 16) | (g << 8) | b);
}

int	sin_gradient(int iter, int max_iter)
{
	double	freq;
	double	amp;
	int		r;
	int		g;
	int		b;

	freq = 0.085;
	amp = 120.0;
	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(freq * iter + 0.00) * (1.00 * amp) + 128.0);
	g = (int)(sin(freq * iter + 2.20) * (0.60 * amp) + 128.0);
	b = (int)(sin(freq * iter + 0.40) * (1.00 * amp) + 128.0);
	return ((r << 16) | (g << 8) | b);
}

int	flame_gradient(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / (double)max_iter;
	r = (int)(pow(t, 0.7) * 255.0);
	g = (int)(pow(t, 1.3) * 180.0);
	b = (int)(pow(t, 2.0) * 80.0);
	return ((r << 16) | (g << 8) | b);
}

int	ocean_gradient(int iter, int max_iter)
{
	double	freq;
	double	amp;
	int		r;
	int		g;
	int		b;

	freq = 0.060;
	amp = 120.0;
	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(freq * iter + 2.40) * (0.45 * amp) + 128.0);
	g = (int)(sin(freq * iter + 0.00) * (1.10 * amp) + 128.0);
	b = (int)(sin(freq * iter + 4.10) * (0.80 * amp) + 128.0);
	return ((r << 16) | (g << 8) | b);
}
