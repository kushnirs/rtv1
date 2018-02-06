/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:11:57 by skushnir          #+#    #+#             */
/*   Updated: 2017/12/29 11:45:25 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(char const *s, size_t n)
{
	int i;

	if (!s)
		return (ft_putnstr("(null)", n));
	i = 0;
	while (s[i] && n-- > 0)
	{
		ft_putchar(s[i]);
		i++;
	}
	return ;
}

void	ft_putunstr(int const *s, size_t n)
{
	intmax_t	j;

	if (!s)
		return (ft_putnstr("(null)", n));
	j = ft_strulen(s);
	(intmax_t)n < j ? j = n : 0;
	while (*s && (j -= ft_ucharlen(*s)) >= 0)
		ft_putchar(*s++);
	return ;
}
