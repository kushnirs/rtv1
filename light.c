/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:04:08 by sergee            #+#    #+#             */
/*   Updated: 2018/02/23 21:14:33 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_p_d(t_point *l, t_point *n, t_point *v, int s, double intens)
{
	double		rv;
	double		nl;
	double		i;
	t_point		r;

	i = 0;
	nl = v_scal(n, l);
	nl > 0 ? i += intens * nl /
				(v_len(n) * v_len(l)) : 0;
	if (s >= 0)
	{
		r = reflect_ray(*n, *l);
		rv = v_scal(&r, v);
		rv > 0 ? i += intens * pow(rv / (v_len(&r) * v_len(v)), s) : 0;
	}
	return (i);
}

static t_point	ft_light_p_d(t_point pnv[3], t_light *light, t_obj *obj)
{
	t_closest	closest;
	double		max;
	t_point		l;

	if (!ft_strcmp(light->type, "point"))
	{
		l = v_sub(&light->direction, &pnv[0]);
		max = 1;
	}
	else
	{
		l = light->direction;
		max = MAX_SIZE;
	}
	closest = intersections(&((t_scene){&pnv[0], &l,
		obj, NULL, 0, 0.001, max}));
	if (closest.closest_obj)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
	return (l);
}

double	ft_light(t_point pnv[3], int s, t_light *light, t_obj *obj)
{
	int			a;
	double		i;
	t_point		l;

	i = 0;
	a = -1;
	while (++a < 4)
	{
		if (!ft_strcmp(light[a].type, "ambient"))
			i += light[a].intensity;
		else
		{
			l = ft_light_p_d(pnv, &light[a], obj);
			if (l.x != MAX_SIZE && l.y != MAX_SIZE)
				i += ft_p_d(&l, &pnv[1], &pnv[2], s, light[a].intensity);
		}
	}
	i > 1 ? i = 1 : 0;
	return (i);
}
