/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:07:28 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/02 10:15:21 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_read_fd(int fd, t_list *tmp, char *buff)
{
	int		fin;
	char	*tm_;

	tm_ = NULL;
	fin = 0;
	while (!ft_strchr(tmp->content, '\n')
		&& (fin = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tm_ = tmp->content;
		buff[fin] = 0;
		if (!(tmp->content = ft_strjoin(tm_, buff)))
			return (-1);
		ft_memdel((void**)&tm_);
	}
	return (fin);
}

static t_list	*ft_check_fd(int fd, t_list **descr)
{
	t_list	*tmp;

	while (*descr)
	{
		if ((int)(*descr)->content_size == fd)
			return (*descr);
		descr = &(*descr)->next;
	}
	if (!(tmp = ft_lstnew("", 1)))
		return (NULL);
	ft_lstadd(descr, tmp);
	(*descr)->content_size = fd;
	return (*descr);
}

int				get_next_line(const int fd, char **line)
{
	size_t			i;
	char			buff[BUFF_SIZE + 1];
	t_list			*tmp;
	char			*tm_;
	static t_list	*descr;

	tm_ = NULL;
	if (fd < 0 || !line || !(tmp = ft_check_fd(fd, &descr))
		|| ft_read_fd(fd, tmp, buff) == -1)
		return (-1);
	*line = NULL;
	if (!*(char *)tmp->content)
		return (0);
	i = ft_strlen(tmp->content);
	if (ft_strchr(tmp->content, '\n'))
		i = i - ft_strlen(ft_strchr(tmp->content, '\n'));
	if (!(*line = ft_strsub(tmp->content, 0, i)))
		return (-1);
	tm_ = tmp->content;
	tmp->content = ft_strchr(tm_ + i, '\n') ?
		ft_strdup(tm_ + i + 1) : ft_strdup(tm_ + i);
	ft_memdel((void **)&tm_);
	return (tmp->content ? 1 : -1);
}
