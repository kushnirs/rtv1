/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:04:08 by sergee            #+#    #+#             */
/*   Updated: 2018/02/19 15:06:04 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_light(t_point *p, t_point *n, t_point *v, int s, t_light *light, t_obj *obj)
{
	t_closest	closest;
	int		a;
	double	t_max;
	double	i;
	t_point	l;
	t_point	r;
	double	rv;
	double	nl;

	i = 0;
	a = -1;
	while (++a < 3)
	{
		if (!ft_strcmp(light[a].type, "ambient"))
			i += light[a].intensity;
		else
		{
			if (!ft_strcmp(light[a].type, "point"))
			{
				l = vector_substr(&light[a].direction, p);
				t_max = 1;
			}
			else
			{
				l =light[a].direction;
				t_max = MAX_SIZE;
			}
			closest = intersections(&((t_scene){p, &l, obj, NULL, 0, 0.001, t_max}));
			if (closest.closest_obj)
				continue;
			nl = vector_scalar(n, &l);
			nl > 0 ? i += light[a].intensity * nl /
				(vector_length(n) * vector_length(&l)) : 0;
			if (s >= 0)
			{
				r = reflect_ray(*n, l);
				rv = vector_scalar(&r, v);
				rv > 0 ? i += light[a].intensity * pow(rv / (vector_length(&r) * vector_length(v)), s) : 0;
			}
		}
	}
	i > 1 ? i = 1 : 0;
	return (i);
}
