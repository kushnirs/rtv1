/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eg_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:47:07 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/27 21:31:36 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_e_nbr(double n, int i)
{
	int	count;

	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	count = 0;
	while ((n = n / 10) >= 1)
		count++;
	ft_f_nbr(n *= 10, i);
	ft_strchr(g_f.conversion, 'e') ? ft_putstr("e+") : ft_putstr("E+");
	if (count < 10)
		ft_putstr("0");
	ft_nbr(count, 0);
}

void	ft_el_nbr(t_ld n, int i)
{
	int	count;

	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	count = 0;
	while ((n = n / 10) >= 1)
		count++;
	ft_fl_nbr(n *= 10, i);
	ft_strchr(g_f.conversion, 'e') ? ft_putstr("e+") : ft_putstr("E+");
	if (count < 10)
		ft_putstr("0");
	ft_nbr(count, i);
}

size_t	ft_e_nbrlen(double n, int i)
{
	int		count;
	size_t	len;

	if (n != n || n == INF)
		return (3);
	if (n < 0)
		n = -n;
	count = 0;
	while ((n = n / 10) >= 1)
		count++;
	len = ft_f_nbrlen(n *= 10, i) + 3;
	count < 10 ? len++ : 0;
	return (len);
}

size_t	ft_el_nbrlen(t_ld n, int i)
{
	int		count;
	size_t	len;

	if (n != n || n == INF)
		return (3);
	if (n < 0)
		n = -n;
	count = 0;
	while ((n = n / 10) >= 1)
		count++;
	len = ft_f_nbrlen(n *= 10, i) + 3;
	count < 10 ? len++ : 0;
	return (len);
}
