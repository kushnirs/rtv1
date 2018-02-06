/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decnbrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 11:20:55 by sergee            #+#    #+#             */
/*   Updated: 2017/12/28 11:21:25 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_nbrlen(int nbr)
{
	int				i;
	unsigned long	nb;

	i = 1;
	nb = nbr;
	if (nbr < 0)
		nb = -nb;
	nbr < 0 ? i++ : 0;
	while ((nb = nb / 10) >= 1)
		i++;
	return (i);
}

size_t		ft_unbrlen(t_ui nbr)
{
	long	i;

	i = 1;
	while ((nbr = nbr / 10) >= 1)
		i++;
	return (i);
}

size_t		ft_lnbrlen(long nbr)
{
	int				i;
	unsigned long	nb;

	i = 1;
	nb = nbr;
	if (nbr < 0)
		nb = -nb;
	nbr < 0 ? i++ : 0;
	while ((nb = nb / 10) >= 1)
		i++;
	return (i);
}

size_t		ft_ulnbrlen(t_ul nbr)
{
	int		i;
	t_ul	nb;

	i = 1;
	nb = nbr;
	while ((nb = nb / 10) >= 1)
		i++;
	return (i);
}
