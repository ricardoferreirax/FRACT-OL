/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:19:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/05 11:18:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	zoom_at_point(int x, int y, double zoom_factor, t_fractol *f)
{
	double	mouse_re;
	double	mouse_im;
	double	scale_x;
	double	scale_y;

	scale_x = (4.0 / WIDTH) * f->zoom;
	scale_y = (4.0 / HEIGHT) * f->zoom;
	mouse_re = (x - WIDTH / 2) * scale_x + f->offset_x;
	mouse_im = (y - HEIGHT / 2) * scale_y + f->offset_y;
	f->zoom *= zoom_factor;
	f->offset_x = mouse_re - (mouse_re - f->offset_x) * zoom_factor;
	f->offset_y = mouse_im - (mouse_im - f->offset_y) * zoom_factor;
}

void	handle_mouse_key(int keycode, int x, int y, t_fractol *f)
{
	(void)x;
	if (keycode == MOUSE_WHEEL_UP)
		zoom_at_point(x, y, 0.8, f);
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom_at_point(x, y, 1.2, f);
	render_fractal(f);
}
