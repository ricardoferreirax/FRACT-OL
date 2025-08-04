/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 16:31:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	poli_gradiant(int iter, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	sin_tripy(int iter, int max_iter)
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(0.1 * iter + 0) * 127 + 128);
	g = (int)(sin(0.1 * iter + 2) * 127 + 128);
	b = (int)(sin(0.1 * iter + 4) * 127 + 128);
	return ((r << 16) | (g << 8) | b);
}

int	fire_thing(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(t * 255);
	g = (int)(t * t * 128);
	b = (int)(t * t * t * 64);
	return ((r << 16) | (g << 8) | b);
}

int	purple_trip(int iter, int max_iter)
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(0.1 * iter + 2.0) * 60 + 120);
	g = 0;
	b = (int)(sin(0.1 * iter + 0.5) * 60 + 155);
	return ((r << 16) | (g << 8) | b);
}

int	colorize(int iter, t_fractol *f)
{
	if (iter > f->c_max_iter)
		iter = f->c_max_iter;
	return (f->color_table[iter]);
}
