/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:45:03 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/13 17:15:39 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		k;
	char	*tmp;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	tmp = ft_strnew(i);
	k = 0;
	while (i > 0)
		tmp[k++] = str[--i];
	return (tmp);
}
