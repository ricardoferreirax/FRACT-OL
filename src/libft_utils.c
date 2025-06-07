/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:34:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/07 21:46:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *s)
{
	int		i;
	ssize_t	ret;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ret = write(1, &s[i], 1);
		(void)ret;
		i++;
	}
}

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
