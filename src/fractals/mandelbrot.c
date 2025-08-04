/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:21:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 15:36:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	mandelbrot(t_complex c, int c_max_iter)
{
	t_complex	z;
	int			i;

	i = 0;
	z.re = 0;
	z.im = 0;
	while (i < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		z = c_add(c_mult(z, z), c);
		i++;
	}
	return (i);
}
