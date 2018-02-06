/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:55:47 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 18:09:00 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *memptr1, const void *memptr2, size_t num)
{
	unsigned int	i;

	i = 0;
	while (i < num)
	{
		if ((unsigned char)*((unsigned char*)memptr1 + i) != \
			(unsigned char)*((unsigned char*)memptr2 + i))
		{
			return ((unsigned char)*((unsigned char*)memptr1 + i) - \
				(unsigned char)*((unsigned char*)memptr2 + i));
		}
		i++;
	}
	return (0);
}
