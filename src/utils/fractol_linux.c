/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:20:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/05 09:49:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

#ifdef __linux__

void fractol_linux_cleanup(void *mlx)
{
    mlx_loop_end(mlx);
    mlx_destroy_display(mlx);
}
#else
void fractol_linux_cleanup(void *mlx)
{
    (void)mlx;
}
#endif