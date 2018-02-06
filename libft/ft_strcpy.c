/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 00:40:07 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 13:49:20 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *destptr, const char *srcptr)
{
	int		i;

	i = -1;
	while (srcptr[++i])
		destptr[i] = srcptr[i];
	destptr[i] = 0;
	return (destptr);
}
