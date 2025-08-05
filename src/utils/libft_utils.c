/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:34:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/04 22:46:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	if (n == 0)
		return (0);
	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	idx = 0;
	while (tmp_s1[idx] && tmp_s2[idx] && tmp_s1[idx] == tmp_s2[idx]
		&& idx < n - 1)
		idx++;
	return (tmp_s1[idx] - tmp_s2[idx]);
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
