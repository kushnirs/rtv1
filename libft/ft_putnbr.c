/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:47:07 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 17:21:50 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int				a;
	int				c;
	unsigned int	b;

	b = n;
	if (n < 0)
	{
		b = n * -1;
		write(1, "-", 1);
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
		write(1, &c, 1);
	}
}
