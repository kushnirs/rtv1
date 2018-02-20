/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayobj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:03:09 by sergee            #+#    #+#             */
/*   Updated: 2018/02/20 12:51:39 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point	raysphere(t_point *o, t_point *d, t_obj *obj)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = vector_substr(o, &obj->c);
	k[0] = vector_scalar(d, d);
	k[1] = 2 * vector_scalar(&oc, d);
	k[2] = vector_scalar(&oc, &oc) - obj->radius * obj->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);
	return (t);
}

int intersect_cylinder(t_point *d, t_point *o, t_point *v, t_obj *obj, t_point *p2, double t)
{
	t_point	p;
	t_point	a;
	t_point	b;
	double lox;
	double k[2];

	if (k < 0)
		return (0);
	p = vector_mult(d, t);
	p = vector_addition(o, &p);
	a = vector_substr(&p, &obj->c);
	k[0] = vector_scalar(v, &a);
	b = vector_substr(&p, p2);
	k[1] = vector_scalar(v, &b);
	lox = vector_scalar(v, &a);
	p = vector_mult(v, lox);
	p = vector_substr(&a, &p);
	lox = vector_scalar(&p, &p) - obj->radius * obj->radius;
	if (k[0] > 0 && k[1] < 0 && t > 0)
		return (1);
	return (0);
}

t_point	raycylinder(t_point *o, t_point *d, t_obj *obj)
{
	t_point	p;
	t_point	v;
	t_point t;
	t_point	a;
	t_point	b;
	double	disc;
	double	k[3];

	v = vector_substr(&obj->d, &obj->c);
	v = vector_mult(&v, 1 / vector_length(&v));
	p = vector_substr(o, &obj->c);
	a = vector_mult(&v, vector_scalar(d, &v));
	a = vector_substr(d, &a);
	k[0] = vector_scalar(&a, &a);
	b = vector_mult(&v, vector_scalar(&p, &v));
	b = vector_substr(&p, &b);
	k[1] = 2 * vector_scalar(&a, &b);
	k[2] = vector_scalar(&b, &b) - obj->radius * obj->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);
	k[0] = intersect_cylinder(d, o, &v, obj, &obj->d, t.x);
	k[1] = intersect_cylinder(d, o, &v, obj, &obj->d, t.y);
	k[0] != 1 ?	t.x = MAX_SIZE : 0;
	k[1] != 1 ? t.y = MAX_SIZE : 0;
	return (t);
}

t_point	rayplane(t_point *o, t_point *d, t_obj *obj)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = vector_substr(o, &obj->c);
	k[0] = vector_scalar(d, &obj->d);
	k[1] = vector_scalar(&oc, &obj->d);
	if (k[0] > 0)
	{
		t.x = -k[1] / k[0];
		t.y = MAX_SIZE;
		return (t);		
	}
	return ((t_point){MAX_SIZE, MAX_SIZE, 0});
}
