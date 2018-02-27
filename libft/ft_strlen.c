/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 23:56:36 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/27 12:21:24 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_ucharlen(int c)
{
	if (MB_CUR_MAX == 1 || c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (0);
}

size_t		ft_strlen(const char *string)
{
	size_t	i;

	if (!string)
		return (6);
	i = 0;
	while (string[i])
		i++;
	return (i);
}

size_t		ft_strulen(const int *string)
{
	size_t	i;

	if (!string)
		return (6);
	i = 0;
	while (*string)
		i += ft_ucharlen(*string++);
	return (i);
}

size_t		ft_strnlen(const char *string, size_t n)
{
	size_t	i;

	if (!string)
		return (6);
	i = 0;
	while (string[i] && n-- > 0)
		i++;
	return (i);
}

size_t		ft_strunlen(const int *string, size_t n)
{
	size_t		i;
	intmax_t	j;

	if (!string)
		return (6);
	j = ft_strulen(string);
	(intmax_t)n < j ? j = n : 0;
	i = 0;
	while (*string && (j -= ft_ucharlen(*string)) >= 0)
		i += ft_ucharlen(*string++);
	return (i);
}
