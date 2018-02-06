/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 05:01:26 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 12:19:39 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destptr, const char *srcptr, size_t num)
{
	unsigned int	i;
	unsigned int	a;

	a = ft_strlen(srcptr);
	i = -1;
	while (++i < num)
	{
		if (i < a)
			destptr[i] = srcptr[i];
		else
			destptr[i] = 0;
	}
	return (destptr);
}
