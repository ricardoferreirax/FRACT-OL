/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:01:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/08 19:55:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	handle_key_suite(int keycode, t_fractol *f)
{
	if (keycode == KEY_C)
	{
		f->color_mode = (f->color_mode + 1) % 4;
		update_color(f);
	}
	else if (keycode == KEY_H)
	{
		ft_putstr("\nCommands :\n");
		ft_putstr(" - Zoom with mouse and move with arrows or WASD\n");
        ft_putstr(" - Press J (Julia), M (Mandelbrot), B (Burning) or P to");
        ft_putstr ("change the fractal\n");
		ft_putstr(" - Press O and I to increase or decrease precision\n");
		ft_putstr(" - Press C to change color\n");
		ft_putstr(" - Press ESC to quit\n");
	}
}

static void	handle_key_iterations(int keycode, t_fractol *f)
{
	if (keycode == KEY_O)
	{
		if (f->c_max_iter < ITER_TRESHOLD)
		{
			f->c_max_iter += 10;
			update_color(f);
		}
		else
			ft_putstr("Maximum iterations reached!\n");
	}
	else if (keycode == KEY_I)
	{
		if (f->c_max_iter > 0)
		{
			f->c_max_iter -= 10;
			update_color(f);
		}
		else
			ft_putstr("Minimum iterations reached!\n");
	}
}

static void	handle_fractal_keys(int keycode, t_fractol *f)
{
	if (keycode == KEY_B)
	{
		ft_putstr("Switched to Burning Ship\n");
		f->type = "burningship";
	}
	else if (keycode == KEY_M)
	{
		ft_putstr("Switched to Mandelbrot\n");
		f->type = "mandelbrot";
	}
	else if (keycode == KEY_J)
    {
	    ft_putstr("Switched to Julia\n");
	    f->type = "julia";
	    set_default_julia(f);
    }
	else if (keycode == KEY_P)
	{
		ft_putstr("Switched to Phoenix\n");
	    f->type = "phoenix";
	    set_default_phoenix(f);
	}
}

int	handle_key(int keycode, void *param)
{
    t_fractol *f;

    f = (t_fractol *)param;
	if (keycode == KEY_ESC)
		exit_fractol(QUIT, f);
	else if (keycode == KEY_W || keycode == KEY_UP)
		f->offset_y -= 0.4 * f->zoom;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		f->offset_x -= 0.4 * f->zoom;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		f->offset_y += 0.4 * f->zoom;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		f->offset_x += 0.4 * f->zoom;
    handle_fractal_keys(keycode, f); 
    handle_key_iterations(keycode, f);
	handle_key_suite(keycode, f);
	render_fractal(f);
	return (0);
}
