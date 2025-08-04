/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:55:11 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 15:57:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	check_julia(char **av)
{
	double	a;
	double	b;

	a = ft_atof(av[2]);
	b = ft_atof(av[3]);
	if ((a >= -2.0 && a <= 2.0) && (b >= -2.0 && b <= 2.0))
		return (1);
	else
		return (0);
}

static int	check_phoenix(char **av)
{
	double	p_re;
	double	p_im;
	double	c_re;
	double	c_im;

	p_re = ft_atof(av[2]);
	p_im = ft_atof(av[3]);
	c_im = ft_atof(av[4]);
	c_re = ft_atof(av[5]);
	if ((p_re >= -1.0 && p_re <= 1.0) && (p_im >= -1.0 && p_im <= 1.0)
		&& (c_re >= -1.0 && c_re <= 1.0) && (c_im >= -1.0 && c_im <= 1.0))
		return (1);
	else
		return (0);
}

void	check_input(t_fractol *f, int ac, char **av)
{
	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		f->type = "mandelbrot";
	else if (ac == 4 && !ft_strncmp(av[1], "julia", 5) && check_julia(av))
	{
		f->type = "julia";
		f->julia_re = atof(av[2]);
		f->julia_im = atof(av[3]);
	}
	else if (ac == 2 && !ft_strncmp(av[1], "burningship", 11))
		f->type = "burningship";
	else if (ac == 6 && !ft_strncmp(av[1], "phoenix", 7 && check_phoenix(av)))
	{
		f->type = "phoenix";
		f->pv.k.reel = ft_atof(av[2]);
		f->pv.k.imag = ft_atof(av[3]);
		f->pv.c.reel = ft_atof(av[4]);
		f->pv.c.imag = ft_atof(av[5]);
	}
	else
		exit_fractol(INPUT, f);
}