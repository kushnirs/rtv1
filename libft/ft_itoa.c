/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 23:06:38 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 17:32:23 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_nbr(char *str, int n, int a, unsigned int b)
{
	int				z;
	int				c;

	z = 0;
	if (n < 0)
	{
		str[z] = '-';
		z = 1;
	}
	while (a > 0)
	{
		c = b / a;
		b = b - c * a;
		a = a / 10;
		str[z] = c + 48;
		z++;
	}
	str[z] = 0;
}

char			*ft_itoa(int n)
{
	int				a;
	int				c;
	unsigned int	b;
	char			*str;

	b = n;
	a = 1;
	c = 0;
	if (n < 0)
		b = n * -1;
	while ((b / a) >= 10)
	{
		a = a * 10;
		c++;
	}
	if (n < 0)
		str = (char*)malloc(sizeof(char) * (c + 2));
	else
		str = (char*)malloc(sizeof(char) * (c + 1));
	if (str == NULL)
		return (NULL);
	ft_nbr(str, n, a, b);
	return (str);
}
