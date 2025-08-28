/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:20:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:17:36 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

#ifdef __linux__

void	fractol_linux_cleanup(void *mlx)
{
	mlx_loop_end(mlx);
	mlx_destroy_display(mlx);
}
#else

void	fractol_linux_cleanup(void *mlx)
{
	(void)mlx;
}
#endif