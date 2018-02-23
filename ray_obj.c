/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:03:09 by sergee            #+#    #+#             */
/*   Updated: 2018/02/23 20:22:39 by sergee           ###   ########.fr       */
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
	t = q_equation(k);
	return (t);
}

double intersect_cyl_con(t_point *d, t_point *o, t_point *v, t_obj *obj, t_point *p2, double t)
{
	t_point	p;
	t_point	a;
	double k[2];

	if (t < 0)
		return (MAX_SIZE);
	p = v_mult(d, t);
	p = v_add(o, &p);
	a = v_sub(&p, &obj->c);
	k[0] = v_scal(v, &a);
	a = v_sub(&p, p2);
	k[1] = v_scal(v, &a);
	if (k[0] > 0 && k[1] < 0 && t > 0)
		return (t);
	return (MAX_SIZE);
}

t_point	raycylinder(t_point *o, t_point *d, t_obj *obj)
{
	t_point	p;
	t_point	v;
	t_point t;
	t_point	a[2];
	double	k[3];

	v = v_sub(&obj->d, &obj->c);
	v = v_mult(&v, 1 / v_len(&v));
	p = v_sub(o, &obj->c);
	a[0] = v_mult(&v, v_scal(d, &v));
	a[0] = v_sub(d, &a[0]);
	k[0] = v_scal(&a[0], &a[0]);
	a[1] = v_mult(&v, v_scal(&p, &v));
	a[1] = v_sub(&p, &a[1]);
	k[1] = 2 * v_scal(&a[0], &a[1]);
	k[2] = v_scal(&a[1], &a[1]) - obj->radius * obj->radius;
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, &v, obj, &obj->d, t.x);
	t.y = intersect_cyl_con(d, o, &v, obj, &obj->d, t.y);
	return (t);
}

t_point	raycone(t_point *o, t_point *d, t_obj *obj)
{
	t_point	p;
	t_point	v;
	t_point t;
	t_point	a[2];
	double	angle;
	double	k[3];

	angle = M_PI * obj->radius / 180;
	v = v_sub(&obj->d, &obj->c);
	v = v_mult(&v, 1 / v_len(&v));
	p = v_sub(o, &obj->d);
	a[0] = v_mult(&v, v_scal(d, &v));
	a[0] = v_sub(d, &a[0]);
	k[0] = cos(angle) * cos(angle) * v_scal(&a[0], &a[0]);
	k[0] -= sin(angle) * sin(angle) * v_scal(d, &v) * v_scal(d, &v);
	a[1] = v_mult(&v, v_scal(&p, &v));
	a[1] = v_sub(&p, &a[1]);
	k[1] = 2 * cos(angle) * cos(angle) * v_scal(&a[0], &a[1]);
	k[1] -= 2 * sin(angle) * sin(angle) * v_scal(d, &v) * v_scal(&p, &v);
	k[2] = cos(angle) * cos(angle) * v_scal(&a[1], &a[1]);
	k[2] -= sin(angle) * sin(angle) * v_scal(&p, &v) * v_scal(&p, &v);
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, &v, obj, &obj->d, t.x);
	t.y = intersect_cyl_con(d, o, &v, obj, &obj->d, t.y);
	return (t);
}

t_point	rayplane(t_point *o, t_point *d, t_obj *obj)
{
	t_point	oc;
	t_point	t;
	double	k[2];

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
