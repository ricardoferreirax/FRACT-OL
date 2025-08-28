/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:19:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:22:52 by rickymercur      ###   ########.fr       */
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

int	handle_mouse_key(int keycode, int x, int y, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (keycode == MOUSE_WHEEL_UP)
		zoom_at_point(x, y, 0.8, f);
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom_at_point(x, y, 1.2, f);
	render_fractal(f);
	return (0);
}
