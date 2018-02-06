/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 07:52:52 by skushnir          #+#    #+#             */
/*   Updated: 2017/10/28 09:02:29 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	int i;

	i = 0;
	while (string[i])
		i++;
	while (i >= 0)
	{
		if (string[i] == symbol)
			return (&((char*)string)[i]);
		i--;
	}
	return (NULL);
}
