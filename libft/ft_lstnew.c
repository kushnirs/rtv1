/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 21:43:22 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/30 12:59:52 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*begin;

	begin = NULL;
	if ((begin = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		if ((begin->content = malloc(content_size)) == NULL)
			return (NULL);
		begin->content = ft_memcpy(begin->content, content, content_size);
		begin->content_size = content_size;
	}
	else
	{
		begin->content = NULL;
		begin->content_size = 0;
	}
	begin->next = NULL;
	return (begin);
}
