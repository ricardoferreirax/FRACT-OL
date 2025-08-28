/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:03:22 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	main(int ac, char **av)
{
	t_fractol	f;

	init_defaults(&f);
	check_input(&f, ac, av);
	init_fractol(&f);
	ft_putstr("Program launched, press h for help\n");
	render_fractal(&f);
	mlx_key_hook(f.win, handle_key, &f);
	mlx_mouse_hook(f.win, handle_mouse_key, &f);
	mlx_hook(f.win, 17, 0, handle_close, &f);
	mlx_loop(f.mlx);
	return (0);
}
