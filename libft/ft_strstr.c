/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 09:15:24 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/31 10:23:19 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *string1, const char *string2)
{
	int i;
	int g;

	if (*string1 == 0 && *string2 == 0)
		return ((char*)string1);
	i = 0;
	while (string1[i])
	{
		g = 0;
		while (string2[g])
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
	return (NULL);
}
