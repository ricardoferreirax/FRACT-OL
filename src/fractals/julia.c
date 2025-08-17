/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:53:58 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/17 20:45:34 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	julia(t_complex c, t_complex z, int c_max_iter)
{
	int	nb_iter;

	nb_iter = 0;
	while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		z = c_add(c_mult(z, z), c);
		nb_iter++;
	}
	return (nb_iter);
}

void	set_default_julia(t_fractol *f)
{
	f->julia_re = -0.8;
	f->julia_im = 0.156;
}
