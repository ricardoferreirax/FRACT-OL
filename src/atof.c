/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:41:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/09 09:41:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

char	*parse_integer_part(char *str, double *result, int *sign)
{
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10.0 + (*str - '0');
		str++;
	}
	return (str);
}

void	parse_fractional_part(char *str, double *fraction, int *decimal_places)
{
	while (*str >= '0' && *str <= '9')
	{
		*fraction = *fraction * 10.0 + (*str - '0');
		(*decimal_places)++;
		str++;
	}
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		decimal_places;

	result = 0.0;
	fraction = 0.0;
	decimal_places = 0;
	str = parse_integer_part(str, &result, &sign);
	if (*str == '.')
		parse_fractional_part(str + 1, &fraction, &decimal_places);
	while (decimal_places-- > 0)
		fraction /= 10.0;
	return (sign * (result + fraction));
}
