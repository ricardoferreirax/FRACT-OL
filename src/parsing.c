/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:55:11 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/05 10:58:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	nmb;
	int		power;

	nmb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
		nmb = nmb * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	power = 1;
	while (ft_isdigit(*str))
	{
		nmb = nmb * 10 + (*str++ - '0');
		power *= 10;
	}
	return (sign * nmb / power);
}

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
	if (ac == 2 && !ft_strcmp(av[1], "mandelbrot"))
		f->type = "mandelbrot";
	else if (ac == 4 && !ft_strcmp(av[1], "julia") && check_julia(av))
	{
		f->type = "julia";
		f->julia_re = ft_atof(av[2]);
		f->julia_im = ft_atof(av[3]);
	}
	else if (ac == 2 && !ft_strcmp(av[1], "burningship"))
		f->type = "burningship";
	else if (ac == 6 && !ft_strcmp(av[1], "phoenix") && check_phoenix(av))
	{
		f->type = "phoenix";
		f->pv.p.re = ft_atof(av[2]);
		f->pv.p.im = ft_atof(av[3]);
		f->pv.c.re = ft_atof(av[4]);
		f->pv.c.im = ft_atof(av[5]);
	}
	else
		exit_fractol(INPUT, f);
}
