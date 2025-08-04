/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:53:58 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 22:36:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	julia(t_complex c, t_complex z, int c_max_iter)
{
	int	i;

	i = 0;
	while (i < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		z = c_add(c_mult(z, z), c);
		i++;
	}
	return (i);
}

void	set_default_julia(t_fractol *f)
{
	f->julia_re = -0.8;
	f->julia_im = 0.156;
}
