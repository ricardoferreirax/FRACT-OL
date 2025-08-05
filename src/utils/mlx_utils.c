/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:11:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 22:50:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <../minilibx-linux/mlx.h>

void	mlx_destroy_all(t_fractol *fractal)
{
	if (fractal->img.img)
		mlx_destroy_image(fractal->mlx, fractal->img.img);
	if (fractal->win)
		mlx_destroy_window(fractal->mlx, fractal->win);
	if (fractal->mlx)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
	}
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    int offset;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
        dst = img->addr + offset;
        *(unsigned int *)dst = color;
    }
}
