/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:35:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/19 20:48:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	burning_ship(t_complex c, int c_max_iter)
{
	t_complex	z;
	int			nb_iter;

	nb_iter = 0;
	z.re = 0;
	z.im = 0;
	while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		z.re = ft_abs(z.re);
		z.im = ft_abs(z.im);
		z = c_add(c_mult(z, z), c);
		nb_iter++;
	}
	return (nb_iter);
}
