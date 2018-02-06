/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:31:22 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 10:32:54 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				a;
	int				c;
	unsigned int	b;

	b = n;
	if (n < 0)
	{
		b = n * -1;
		write(fd, "-", 1);
	}
	a = 1;
	while ((b / a) >= 10)
		a = a * 10;
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		c = c + 48;
		a = a / 10;
		write(fd, &c, 1);
	}
}
