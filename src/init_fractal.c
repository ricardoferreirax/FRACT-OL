/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:17:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/02 11:56:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_graphics(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		return ;
	fractal->res_width = WIDTH;
	fractal->res_height = HEIGHT;
	fractal->win = mlx_new_window(fractal->mlx, fractal->res_width,
			fractal->res_height, "Fract-ol");
	if (!fractal->win)
		return ;
	fractal->img = mlx_new_image(fractal->mlx, fractal->res_width,
			fractal->res_height);
	if (!fractal->img)
		return ;
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	fractal->zoom = 1.0;
	fractal->offset_x = 0;
	fractal->offset_y = 0;
	fractal->max_iter = 50;
	fractal->color_scheme = 0;
}

void	init_fractal(t_fractal *fractal, int argc, char **argv)
{
	init_graphics(fractal);
	if (!fractal->mlx)
		return ;
	ft_parse_args(fractal, argc, argv);
}
