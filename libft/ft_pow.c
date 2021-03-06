/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 23:50:42 by sergee            #+#    #+#             */
/*   Updated: 2018/01/09 23:51:05 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double i, double a)
{
	double res;

	if (a <= 0)
		return (1);
	res = i;
	while (a-- > 1)
		res *= i;
	return (res);
}
