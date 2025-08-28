/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:11:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:19:29 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	handle_close(void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	exit_fractol(0, f);
	return (0);
}
