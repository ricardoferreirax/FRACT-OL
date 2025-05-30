/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/30 11:19:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	color_blue_violet(double t)
{
	return ((int)(9 * (1 - t) * t * t * t * 255) << 16 |
			(int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8 |
			(int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
}

int	color_red_yellow(double t)
{
	return ((int)(t * 255) << 16 |
			(int)(t * t * 255) << 8 |
			(int)((1 - t) * 255));
}

int	color_blue_gradient(double t)
{
	return ((int)(t * 255) << 8 |
			(int)((1 - t) * 255) << 16);
}

int	color_green_turquoise(double t)
{
	return ((int)(t * 255) << 8 |
			(int)(t * t * 255) << 16 |
			(int)((1 - t) * 255));
}

int	color_pink_white(double t)
{
	return ((int)(t * 255) << 16 |
			(int)(t * 128) << 8 |
			(int)(t * 255));
}
