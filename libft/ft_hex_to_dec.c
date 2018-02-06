/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 23:37:27 by sergee            #+#    #+#             */
/*   Updated: 2018/01/11 19:12:04 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_hex_to_dec(char *str)
{
	long	num;
	int		s;

	if (!str)
		return (0);
	num = 0;
	if (*str == '0' && ft_tolower(*(str + 1)) == 'x')
		str += 2;
	while (*str)
	{
		if (ft_isdigit(*str))
			s = *str - '0';
		else if (ft_isalpha(*str))
		{
			if (ft_tolower(*str) <= 'f')
				s = ft_tolower(*str) - 'a' + 10;
			else
				return (0);
		}
		num = num * 16 + s;
		str++;
	}
	return (num);
}
