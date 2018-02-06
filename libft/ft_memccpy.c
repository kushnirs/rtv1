/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:45:41 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/28 07:16:29 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *source, int ch, size_t count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		*((unsigned char*)dest + i) = \
		(unsigned char)*((unsigned char*)source + i);
		if ((unsigned char)*((unsigned char*)source + i) == (unsigned char)ch)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
