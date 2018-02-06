/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 05:27:17 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/28 06:18:16 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *destptr, const char *srcptr)
{
	int	i;
	int	num;

	i = 0;
	while (destptr[i])
		i++;
	num = 0;
	while (srcptr[num])
	{
		destptr[i] = srcptr[num];
		num++;
		i++;
	}
	destptr[i] = '\0';
	return (destptr);
}
