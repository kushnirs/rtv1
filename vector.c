/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:23:38 by sergee            #+#    #+#             */
/*   Updated: 2018/02/12 08:44:58 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	vector_scalar(t_point *a, t_point *b)
{
	double	tmp;

	tmp = a->x * b->x + a->y * b->y + a->z * b->z;
	return (tmp);
}

t_point vector_substr(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = (t_point){a->x - b->x, a->y - b->y, a->z - b->z};
	return (tmp);
}

t_point vector_addition(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = (t_point){a->x + b->x, a->y + b->y, a->z + b->z};
	return (tmp);
}

t_point	vector_mult(t_point *a, double num)
{
	t_point	tmp;

	tmp = (t_point){a->x * num, a->y * num, a->z * num};
	return (tmp);
}

double	vector_length(t_point *a)
{
	double	tmp;

	tmp = sqrt(a->x * a->x + a->y * a->y  + a->z * a->z);
	return (tmp);
}

t_point	reflect_ray(t_point n, t_point l)
{
	t_point	r;

	r = vector_mult(&n, 2 * vector_scalar(&n, &l));
	r = vector_substr(&r, &l);
	return (r);
}
