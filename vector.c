/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:23:38 by sergee            #+#    #+#             */
/*   Updated: 2018/02/23 10:59:22 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	v_scal(t_point *a, t_point *b)
{
	double	tmp;

	tmp = a->x * b->x + a->y * b->y + a->z * b->z;
	return (tmp);
}

t_point v_sub(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = (t_point){a->x - b->x, a->y - b->y, a->z - b->z};
	return (tmp);
}

t_point v_add(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = (t_point){a->x + b->x, a->y + b->y, a->z + b->z};
	return (tmp);
}

t_point	v_mult(t_point *a, double num)
{
	t_point	tmp;

	tmp = (t_point){a->x * num, a->y * num, a->z * num};
	return (tmp);
}

double	v_len(t_point *a)
{
	double	tmp;

	tmp = sqrt(a->x * a->x + a->y * a->y  + a->z * a->z);
	return (tmp);
}
