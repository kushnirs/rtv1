/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:37:41 by skushnir          #+#    #+#             */
/*   Updated: 2018/01/11 19:27:29 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free(char **arr, unsigned int i)
{
	unsigned int		a;

	a = 0;
	while (a < i)
		free(arr[a++]);
	free(arr);
	return (NULL);
}

static	void	ft_cpy(char *destptr, const char *srcptr, size_t num)
{
	unsigned int		i;

	i = 0;
	while (i < num)
	{
		destptr[i] = srcptr[i];
		i++;
	}
	destptr[i] = '\0';
}

static	int		ft_size(const char *s, char c)
{
	unsigned int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static	char	**ft_delimiter(char **arr, const char *s, char c)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		size;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		size = ft_size(s + i, c);
		arr[j] = (char*)malloc(sizeof(char) * (size + 1));
		if (arr[j] == NULL)
			return (ft_free(arr, j));
		ft_cpy(arr[j], &s[i], size);
		j++;
		i += size;
	}
	arr[j] = 0;
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	unsigned int		i;
	unsigned int		j;
	char				**arr;

	if (!s)
		return (NULL);
	i = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			j++;
		i++;
	}
	if ((arr = (char**)malloc(sizeof(char*) * (j + 1))) == NULL)
		return (NULL);
	return (ft_delimiter(arr, s, c));
}
