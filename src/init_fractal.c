/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:17:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 15:51:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_defaults(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img.img = NULL;
	f->type = NULL;
	f->c_max_iter = 50;
	f->color_mode = 0;
	f->color_table = NULL;
	f->zoom = 1.0;
	f->offset_x = 0;
	f->offset_y = 0;
	f->julia_re = 0;
	f->julia_im = 0;
	f->pv.p.re = 0;
	f->pv.p.im = 0;
	f->pv.c.re = 0;
	f->pv.c.im = 0;
}

void	init_image(t_fractol *f)
{
	t_img	new_img;

	new_img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!new_img.img)
		exit_fractol(MALLOC, f);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel,
			&new_img.line_length, &new_img.endian);
	if (!new_img.addr)
		exit_fractol(MALLOC, f);
	f->img = new_img;
}

void	init_graphics(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		exit_fractol(MALLOC, f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->type);
	if (!f->win)
		exit_fractol(MALLOC, f);
	f->c_max_iter = MAX_ITER;
	f->zoom = 1;
	update_color_table(f);
}
