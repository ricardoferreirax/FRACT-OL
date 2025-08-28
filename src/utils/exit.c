/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:00:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:16:25 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

static void	input_msg(void)
{
	ft_putstr("========================================================\n");
	ft_putstr("Wrong Input! Try this :\n\n");
	ft_putstr("-> ./fractol mandelbrot \n\n-> ./fractol julia <cr> <ci> ");
	ft_putstr("  (cr and ci ∈ [-2.0, 2.0])\n\n");
	ft_putstr("-> ./fractol burningship\n\n");
	ft_putstr("Here are some cool examples for julia params:\n");
	ft_putstr("(0.285 0.01), (-0.8 0.156), (-0.4 0.6)\n");
	ft_putstr("=========================================================");
}

void	free_fractol(t_fractol *f)
{
	if (f->img.img && f->mlx)
		mlx_destroy_image(f->mlx, f->img.img);
	if (f->mlx && f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		fractol_linux_cleanup(f->mlx);
		free(f->mlx);
	}
	if (f->color_table)
		free(f->color_table);
	ft_putstr("Program terminated successfully :) ");
	exit(0);
}

void	exit_fractol(int errcode, t_fractol *f)
{
	if (errcode == QUIT)
	{
		ft_putstr("\nQuitting program...");
		free_fractol(f);
	}
	else if (errcode == MALLOC)
	{
		ft_putstr("\nError! Malloc failed\n");
		free_fractol(f);
	}
	else if (errcode == MLX_FAIL)
	{
		ft_putstr("\nError! MLX failed\n");
		free_fractol(f);
	}
	else if (errcode == INPUT)
	{
		input_msg();
		exit(0);
	}
}
