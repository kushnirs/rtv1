/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:57:37 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 17:26:36 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *string1, const char *string2, size_t len)
{
	unsigned int	i;
	unsigned int	g;

	i = 0;
	while (i < len && string1[i])
	{
		g = 0;
		while (string2[g] && g + i < len)
		{
			if (string2[g] == string1[i + g])
				g++;
			else
				break ;
		}
		if (string2[g] == 0)
			return ((char*)&string1[i]);
		i++;
	}
	if (!*string2 && len == 0)
		return ((char*)string1);
	return (NULL);
}
