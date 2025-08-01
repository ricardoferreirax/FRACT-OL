/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:46:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 12:39:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

int	burning_ship(t_complex c, int max_iter)
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
		z.im = fabs(2 * z.re * z.im) + c.im;
		z.re = fabs(tmp);
		i++;
	}
	return (i);
}
