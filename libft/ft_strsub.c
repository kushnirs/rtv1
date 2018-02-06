/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 00:36:26 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 18:02:54 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*i;

	if (!s)
		return (NULL);
	if ((i = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	j = 0;
	while (j < len)
		i[j++] = s[start++];
	i[j] = 0;
	return (i);
}
