/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 19:44:02 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void	update_color(t_fractol *f)
{
	int	i;

	if (f->color_table)
		free(f->color_table);
	f->color_table = malloc(sizeof(int) * (f->c_max_iter + 1));
	if (!f->color_table)
		exit_fractol(MALLOC, f);
	i = 0;
	while (i <= f->c_max_iter)
	{
		if (f->color_mode == 0)
			f->color_table[i] = polynomial_gradient(i, f->c_max_iter);
		else if (f->color_mode == 1)
			f->color_table[i] = sin_gradient(i, f->c_max_iter);
		else if (f->color_mode == 2)
			f->color_table[i] = flame_gradient(i, f->c_max_iter);
		else if (f->color_mode == 3)
			f->color_table[i] = ocean_gradient(i, f->c_max_iter);
		else
			f->color_table[i] = BLACK;
		i++;
	}
}

int	colorize(int iter, t_fractol *f)
{
	if (iter > f->c_max_iter)
		iter = f->c_max_iter;
	return (f->color_table[iter]);
}
