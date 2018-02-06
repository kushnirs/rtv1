/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 03:19:43 by sergee            #+#    #+#             */
/*   Updated: 2017/12/28 00:25:41 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_x_nbr(t_ui n, t_ul a)
{
	int		i;
	char	*nbr;
	t_ui	num;
	char	str[21];

	num = n;
	i = 0;
	while (num >= 1)
	{
		n = num % 16;
		str[i] = n + 48;
		if (n >= 10 && n <= 15)
			str[i] = ft_strchr(g_f.conversion, 'X') ? n + 55 : n + 87;
		num /= 16;
		i++;
	}
	!i ? (++i && (str[0] = '0')) : 0;
	str[i] = 0;
	while (a > 0 && a-- > ft_strlen(str))
		ft_putchar('0');
	nbr = ft_strrev(str);
	ft_putstr(nbr);
	ft_memdel((void**)&nbr);
	return ;
}

void	ft_x_lnbr(uintmax_t n, t_ul a)
{
	int		i;
	char	*nbr;
	t_ul	num;
	char	str[21];

	num = n;
	i = 0;
	while (num >= 1)
	{
		n = num % 16;
		str[i] = n + 48;
		if (n >= 10 && n <= 15)
			str[i] = ft_strchr(g_f.conversion, 'X') ? n + 55 : n + 87;
		num /= 16;
		i++;
	}
	!i ? (++i && (str[0] = '0')) : 0;
	str[i] = 0;
	while (a > 0 && a-- > ft_strlen(str))
		ft_putchar('0');
	nbr = ft_strrev(str);
	ft_putstr(nbr);
	ft_memdel((void**)&nbr);
	return ;
}

size_t	ft_x_nbrlen(t_ui n)
{
	int		i;
	t_ui	num;
	char	str[21];

	num = n;
	i = 0;
	while (num >= 1)
	{
		n = num % 16;
		str[i] = n + 48;
		if (n >= 10 && n <= 15)
			str[i] = ft_strchr(g_f.conversion, 'X') ? n + 55 : n + 87;
		num /= 16;
		i++;
	}
	!i ? (++i && (str[0] = '0')) : 0;
	str[i] = 0;
	return (ft_strlen(str));
}

size_t	ft_x_lnbrlen(uintmax_t n)
{
	int		i;
	t_ul	num;
	char	str[21];

	num = n;
	i = 0;
	while (num >= 1)
	{
		n = num % 16;
		str[i] = n + 48;
		if (n >= 10 && n <= 15)
			str[i] = ft_strchr(g_f.conversion, 'X') ? n + 55 : n + 87;
		num /= 16;
		i++;
	}
	!i ? (++i && (str[0] = '0')) : 0;
	str[i] = 0;
	return (ft_strlen(str));
}
