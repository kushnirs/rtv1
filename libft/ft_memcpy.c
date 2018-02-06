/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:32:11 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 12:14:35 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	unsigned int	i;
	unsigned char	*c;
	unsigned char	*b;

	c = (unsigned char*)destptr;
	b = (unsigned char*)srcptr;
	i = 0;
	while (i < num)
	{
		c[i] = (unsigned char)b[i];
		i++;
	}
	return (destptr);
}
