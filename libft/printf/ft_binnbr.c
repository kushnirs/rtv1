/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:20:12 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/28 15:20:14 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bin_nbr(uintmax_t n)
{
	int			i;
	uintmax_t	num;
	char		*tmp;
	char		str[65];

	i = 0;
	while (n)
	{
		num = n / 2;
		n = n % 2;
		str[i++] = n + 48;
		n = num;
	}
	str[i] = 0;
	tmp = ft_strrev(str);
	ft_putstr(tmp);
	ft_memdel((void**)&tmp);
	return ;
}

size_t	ft_bin_nbrlen(uintmax_t n)
{
	int			i;
	uintmax_t	num;
	char		str[65];

	i = 0;
	while (n)
	{
		num = n / 2;
		n = n % 2;
		str[i++] = n + 48;
		n = num;
	}
	str[i] = 0;
	return (ft_strlen(str));
}
