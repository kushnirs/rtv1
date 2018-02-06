/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:32:00 by skushnir          #+#    #+#             */
/*   Updated: 2017/11/05 23:32:32 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delete(t_list *alst)
{
	t_list *tmp;

	tmp = 0;
	if (alst)
	{
		while (alst)
		{
			free(alst->content);
			tmp = alst->next;
			free(alst);
			alst = tmp;
		}
	}
	alst = NULL;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *new;
	t_list *new_l;

	tmp = 0;
	new = 0;
	new_l = 0;
	if (lst && f)
	{
		if ((new = f(lst)) == NULL)
			return (NULL);
		tmp = lst->next;
		new_l = new;
		while (tmp)
		{
			if ((new_l->next = f(tmp)) == NULL)
			{
				ft_delete(new);
				return (NULL);
			}
			tmp = tmp->next;
			new_l = new_l->next;
		}
	}
	return (new);
}
