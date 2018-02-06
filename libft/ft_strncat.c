/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 06:10:27 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 16:34:17 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destptr, char *srcptr, size_t num)
{
	unsigned int	i;
	unsigned int	a;

	i = ft_strlen(destptr);
	a = 0;
	while (a < num && srcptr[a])
	{
		destptr[i + a] = srcptr[a];
		a++;
	}
	destptr[i + a] = 0;
	return (destptr);
}
