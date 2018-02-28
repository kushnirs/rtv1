/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:02:22 by sergee            #+#    #+#             */
/*   Updated: 2018/02/28 21:03:09 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_cl.h"

int	check_float(char *str, float *res)
{
	int		i;
	int		len;
	float	num;

	i = -1;
	while (str[++i] != ',' && str[i] != '}' && str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
			continue;
		exit(ft_printf("Wrong floating-point number\n"));
	}
	str[i] == 0 ? exit(ft_printf("missing parameter }\n")) : 0;
	num = 0;
	*res = (float)ft_atoi(str);
	len = ft_nbrlen((int)*res);
	str[len] == '.' ?  num = (float)ft_atoi(&str[len + 1]) : 0;
	len = ft_nbrlen((int)num);
	*res += num / pow(10, len);
	return (i + 1);
}

int	check_coord(char *str, t_point *res)
{
	int		i;
	float	num;

	str[0] != '{' ? exit(ft_printf("Wrong coord\n")) : 0;
	i = 0;
	i += check_float(&str[1], &res->x);
	i += check_float(&str[1 + i], &res->y);
	i += check_float(&str[1 + i], &res->z);
	str[i] != '}' ? exit(ft_printf("missing parameter }\n")) : 0;
	i += str[i + 1] == ',' ? 2 : 1; 
	return (i);
}

int	check_int(char *str, int *res)
{
	int		i;
	int		len;
	float	num;

	i = -1;
	while (str[++i] != ',' && str[i] != '}' && str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
			continue;
		exit(ft_printf("Wrong int number\n"));
	}
	str[i] == 0 ? exit(ft_printf("missing parameter }\n")) : 0;
	*res = ft_atoi(str);
	return (i + 1);
}
