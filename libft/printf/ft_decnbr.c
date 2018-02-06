/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:47:07 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/28 11:22:19 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_nbr(int n, t_ul i)
{
	int		a;
	int		c;
	long	b;

	b = n;
	if (n < 0)
	{
		b = -b;
		ft_putchar('-');
	}
	while (i-- > ft_nbrlen(n))
		ft_putchar('0');
	a = 1;
	while ((b / a) >= 10)
		a = a * 10;
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		c = c + 48;
		a = a / 10;
		ft_putchar(c);
	}
}

void		ft_lnbr(intmax_t n, t_ul i)
{
	long		a;
	int			c;
	uintmax_t	b;

	b = n;
	if (n < 0)
	{
		b = -b;
		ft_putchar('-');
	}
	while (i-- > ft_lnbrlen(n))
		ft_putchar('0');
	a = 1;
	while ((b / a) >= 10)
		a = a * 10;
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		c = c + 48;
		a = a / 10;
		ft_putchar(c);
	}
}

void		ft_unbr(t_ui n, t_ul i)
{
	long			a;
	int				c;
	unsigned int	b;

	while (i-- > ft_unbrlen(n))
		ft_putchar('0');
	b = n;
	a = 1;
	while ((b / a) >= 10)
		a = a * 10;
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		c = c + 48;
		a = a / 10;
		ft_putchar(c);
	}
}

void		ft_ulnbr(uintmax_t n, t_ul i)
{
	t_ul		a;
	long		c;
	uintmax_t	b;

	b = n;
	while (i-- > ft_ulnbrlen(n))
		ft_putchar('0');
	a = 1;
	while ((b / a) >= 10)
		a = a * 10;
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		c = c + 48;
		a = a / 10;
		ft_putchar(c);
	}
}
