/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:41:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/01 11:57:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_isdigit(int c)
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
