/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayobj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:03:09 by sergee            #+#    #+#             */
/*   Updated: 2018/02/21 13:07:49 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point	raysphere(t_point *o, t_point *d, t_obj *obj)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = v_sub(o, &obj->c);
	k[0] = v_scal(d, d);
	k[1] = 2 * v_scal(&oc, d);
	k[2] = v_scal(&oc, &oc) - obj->radius * obj->radius;
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
	double k[2];

	if (k < 0)
		return (0);
	p = v_mult(d, t);
	p = v_add(o, &p);
	a = v_sub(&p, &obj->c);
	k[0] = v_scal(v, &a);
	b = v_sub(&p, p2);
	k[1] = v_scal(v, &b);
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

	v = v_sub(&obj->d, &obj->c);
	v = v_mult(&v, 1 / v_len(&v));
	p = v_sub(o, &obj->c);
	a = v_mult(&v, v_scal(d, &v));
	a = v_sub(d, &a);
	k[0] = v_scal(&a, &a);
	b = v_mult(&v, v_scal(&p, &v));
	b = v_sub(&p, &b);
	k[1] = 2 * v_scal(&a, &b);
	k[2] = v_scal(&b, &b) - obj->radius * obj->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);
	k[0] = intersect_cylinder(d, o, &v, obj, &obj->d, t.x);
	k[1] = intersect_cylinder(d, o, &v, obj, &obj->d, t.y);
	k[0] != 1 ?	t.x = MAX_SIZE : 0;
	k[1] != 1 ? t.y = MAX_SIZE : 0;
	return (t);
}

t_point	raycone(t_point *o, t_point *d, t_obj *obj)
{
	t_point	p;
	t_point	v;
	t_point t;
	t_point	a;
	t_point	b;
	double	angle;
	double	disc;
	double	k[3];

	angle = M_PI * obj->radius / 180;
	v = v_sub(&obj->d, &obj->c);
	v = v_mult(&v, 1 / v_len(&v));
	p = v_sub(o, &obj->d);
	a = v_mult(&v, v_scal(d, &v));
	a = v_sub(d, &a);
	k[0] = cos(angle) * cos(angle) * v_scal(&a, &a);
	k[0] -= sin(angle) * sin(angle) * v_scal(d, &v) * v_scal(d, &v);
	b = v_mult(&v, v_scal(&p, &v));
	b = v_sub(&p, &b);
	k[1] = 2 * cos(angle) * cos(angle) * v_scal(&a, &b);
	k[1] -= 2 * sin(angle) * sin(angle) * v_scal(d, &v) * v_scal(&p, &v);
	k[2] = cos(angle) * cos(angle) * v_scal(&b, &b);
	k[2] -= sin(angle) * sin(angle) * v_scal(&p, &v) * v_scal(&p, &v);
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
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
	t_point	t;
	double	disc;
	double	k[3];

	oc = v_sub(o, &obj->c);
	k[0] = v_scal(d, &obj->d);
	k[1] = v_scal(&oc, &obj->d);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = MAX_SIZE;
		return (t);		
	}
	return ((t_point){MAX_SIZE, MAX_SIZE, 0});
}
