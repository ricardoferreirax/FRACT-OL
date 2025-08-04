/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:33:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 22:36:36 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	phoenix(t_complex z, t_complex p, t_complex c, int c_max_iter)
{
	t_complex	z_prev;
	t_complex	z_next;
	int			i;

	i = 0;
	z_prev.re = 0;
	z_prev.im = 0;
	while (i < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	{
		z_next = c_add(c_add(c_mult(z, z), c_mult(p, z_prev)), c);
		z_prev = z;
		z = z_next;
		i++;
	}
	return (i);
}

void	set_default_phoenix(t_fractol *f)
{
	f->pv.p.re = -0.5667;
	f->pv.p.im = 0.0;
	f->pv.c.re = -0.5;
	f->pv.c.im = 0.5;
}
