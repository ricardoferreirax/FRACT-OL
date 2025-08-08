/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 08:45:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/08 19:55:58 by rmedeiro         ###   ########.fr       */
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
	int	r;
	int	g;
	int	b;
    double freq;
    double amp;

    freq = 0.07;
    amp = 110;
	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(freq * iter + 0.0) * amp + 128);
	g = (int)(sin(freq * iter + 2.1) * amp + 128);
	b = (int)(sin(freq * iter + 4.2) * amp + 128);
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

int ocean_gradient(int iter, int max_iter)
{
    int r;
    int g;
    int b;
    double t;
    
    if (iter >= max_iter)
        return 0x000000;
    t = (double)iter / (double)max_iter;
    r = (int)(t * 50);
    g = (int)(t * 200 + 30);
    b = (int)(t * 255);
    return ((r << 16) | (g << 8) | b);
}
