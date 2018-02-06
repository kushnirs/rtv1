/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 03:17:18 by sergee            #+#    #+#             */
/*   Updated: 2017/12/25 11:33:17 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_o_nbr(t_ui n, t_ul a)
{
	int		i;
	t_ui	num;
	char	*tmp;
	char	str[21];

	i = 0;
	while (n >= 1)
	{
		num = n / 8;
		n = n % 8;
		str[i++] = n + 48;
		n = num;
	}
	str[i] = 0;
	tmp = ft_strrev(str);
	while (a-- > ft_strlen(tmp))
		ft_putchar('0');
	ft_putstr(tmp);
	ft_memdel((void**)&tmp);
	return ;
}

void	ft_o_lnbr(t_ul n, t_ul a)
{
	int		i;
	t_ul	num;
	char	*tmp;
	char	str[21];

	i = 0;
	while (n >= 1)
	{
		num = n / 8;
		n = n % 8;
		str[i++] = n + 48;
		n = num;
	}
	str[i] = 0;
	tmp = ft_strrev(str);
	while (a-- > ft_strlen(tmp))
		ft_putchar('0');
	ft_putstr(tmp);
	ft_memdel((void**)&tmp);
	return ;
}

size_t	ft_o_nbrlen(t_ui n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 8;
		len++;
	}
	return (len);
}

size_t	ft_o_lnbrlen(t_ul n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 8;
		len++;
	}
	return (len);
}
