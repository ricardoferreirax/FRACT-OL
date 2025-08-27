/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:55:11 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/27 18:54:10 by rickymercur      ###   ########.fr       */
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

static int is_simple_number(const char *s)
{
    int digits;
    int dots;

	digits = 0;
	dots = 0;
    if (!s || !*s)
        return 0;
    if (*s == '+' || *s == '-')
        s++;
    if (!*s)
        return 0;
    while (*s)
    {
        if (*s >= '0' && *s <= '9')
            digits++;
        else if (*s == '.')
        {
            if (++dots > 1)
                return (0);
        }
        else
            return (0);
        s++;
    }
    return (digits > 0);
}

static int	check_julia(char **av)
{
	double	a;
	double	b;
	
	if (!is_simple_number(av[2]) || !is_simple_number(av[3]))
        return (0);
	a = ft_atof(av[2]);
	b = ft_atof(av[3]);
	if ((a >= -2.0 && a <= 2.0) && (b >= -2.0 && b <= 2.0))
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
	else
		exit_fractol(INPUT, f);
}
