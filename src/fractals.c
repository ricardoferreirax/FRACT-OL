/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:46:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/07 20:44:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	julia(t_complex z, t_complex c, int max_iter)
{
	int		iter;
	double	tmp;

	iter = 0;
	while (iter < max_iter && (z.re * z.re + z.im * z.im) <= 4)
	{
		tmp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = tmp;
		iter++;
	}
	return (iter);
}

int	mandelbrot(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		tmp;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		tmp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = tmp;
		i++;
	}
	return (i);
}

int	phoenix(t_complex c, int max_iter, double p)
{
	t_complex	z;
	t_complex	prev;
	double		tmp;
	int			i;

	z.re = 0;
	z.im = 0;
	prev.re = 0;
	prev.im = 0;
	i = 0;
	while (i < max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		tmp = z.re * z.re - z.im * z.im + c.re - p * prev.re;
		prev.re = z.re;
		prev.im = z.im;
		z.im = 2 * z.re * z.im + c.im - p * prev.im;
		z.re = tmp;
		i++;
	}
	return (i);
}
