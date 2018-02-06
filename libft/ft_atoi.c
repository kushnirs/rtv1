/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 11:55:33 by skushnir          #+#    #+#             */
/*   Updated: 2018/01/09 23:33:51 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_long(int a, int it, char *s)
{
	if (it > 19)
	{
		if (a == 1 || (a == 1 && *s == '6'))
			return (-1);
		else
			return (0);
	}
	if (a == 1)
		return (-1);
	else
		return (0);
}

static	int	ft_num(const char *s, int i, int a, int z)
{
	long int		num;
	int				it;

	num = 0;
	it = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if ((num = num * z + (s[i++] - 48)) != 0)
				it++;
			z = 10;
			if (num < -1 || it > 19 || (it == 19 && num == 0))
				return (ft_long(a, it, (char*)&s[i - 1]));
		}
		else if (s[i] < '0' || s[i] > '9')
			break ;
	}
	return ((int)num * a);
}

int			ft_atoi(const char *str)
{
	long int		i;
	int				a;
	int				f;
	long int		z;

	i = 0;
	z = 1;
	a = 1;
	f = 0;
	while (((str[i] > 8 && str[i] < 14) || str[i] == 32) || ((str[i] == '-' || \
			str[i] == '+') && str[i + 1] <= '9' && str[i + 1] >= '0'))
		if (str[i++] == '-')
			a = -1;
	return (ft_num(&str[i], f, a, z));
}
