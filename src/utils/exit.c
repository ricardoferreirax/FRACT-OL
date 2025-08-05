/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:00:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 22:45:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void free_fractol(t_fractol *f)
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
		ft_putstr("\nProgram closing...");
		free_fractol(f);
	}
	else if (errcode == MALLOC)
	{
		ft_putstr("\nMalloc Error!\n");
		free_fractol(f);
	}
	else if (errcode == INPUT)
	{
		ft_putstr("Wrong Input ! Try this :\n");    
        ft_putstr("./fractol mandelbrot\n | ./fractol julia <cr> <ci>");
        ft_putstr("where cr and ci are numbers between -2.0 et 2.0)\n");
        ft_putstr("./fractol burningship\n./fractol phoenix <pr> <pi>)");
        ft_putstr(" <cr> <ci> (where numbers included between -1.0 et 1.0)\n\n");
        ft_putstr("Some cool examples of params :\n  Julia\n(0.285 0.01),"); 
        ft_putstr("-1.476 0), (-0.8 0.156), (-0.4 0.6),\n  Phoenix\n(-0.5 0 0.5666 0),");
        ft_putstr("(0.2955 0 -0.4 0.1),\n(-0.25 0 0.4 0), (-0.35 0 0.1 0.6),\n");
        ft_putstr("(-0.8 0 0.6 -0.1), (0 -0.01 0.269 0),\n(-0.53 0 0.55 -0.1)");
		exit(0);
	}
}
