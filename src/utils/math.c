/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:32:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:18:38 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	t_complex	res;

	res.re = a.re + b.re;
	res.im = a.im + b.im;
	return (res);
}

t_complex	c_mult(t_complex a, t_complex b)
{
	t_complex	res;

	res.re = a.re * b.re - a.im * b.im;
	res.im = a.re * b.im + a.im * b.re;
	return (res);
}

t_complex	ft_mapping(int x, int y, t_fractol *f)
{
	t_complex	c_point;

	c_point.re = scale(x, -2.0 * f->zoom + f->offset_x, 2.0 * f->zoom
			+ f->offset_x, WIDTH);
	c_point.im = scale(y, -2.0 * f->zoom + f->offset_y, 2.0 * f->zoom
			+ f->offset_y, HEIGHT);
	return (c_point);
}

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	scale(double to_scale, double n_min, double n_max, double o_max)
{
	return (n_min + (n_max - n_min) * (to_scale - 0) / (o_max - 0));
}
