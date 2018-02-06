/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:38:01 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/29 11:49:02 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int c)
{
	if (MB_CUR_MAX == 1 || c <= 0x7F)
		ft_putchar_fd(c, 1);
	else if (c <= 0x7FF)
	{
		ft_putchar_fd((c >> 6) + 0xC0, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_fd((c >> 12) + 0xE0, 1);
		ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar_fd((c >> 18) + 0xF0, 1);
		ft_putchar_fd(((c >> 12) & 0x3F) + 0x80, 1);
		ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
}
