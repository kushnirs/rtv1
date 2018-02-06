/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:33:52 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 16:02:34 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destptr, const void *srcptr, size_t num)
{
	unsigned int	i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char*)srcptr;
	d = (unsigned char*)destptr;
	while (num-- > 0)
	{
		if (destptr < srcptr)
		{
			d[i] = (unsigned char)s[i];
			i++;
		}
		else if (destptr > srcptr)
			d[num] = (unsigned char)s[num];
	}
	return (destptr);
}
