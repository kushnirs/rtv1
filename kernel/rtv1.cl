/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/24 13:18:49 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_cl.h"
/*
**
***********************************COLOR****************************************
**
*/

static int	parse_color(int c1, int c2, float t)
{
	int dr;
	int dg;
	int db;

	dr = (1 - t) * (float)(c1 / 0x10000 % 256) +
		t * (float)(c2 / 0x10000 % 256);
	dg = (1 - t) * (float)(c1 / 0x100 % 256) + t * (float)(c2 / 0x100 % 256);
	db = (1 - t) * (float)(c1 % 256) + t * (float)(c2 % 256);
	return (dr * 0x10000 + dg * 0x100 + db);
}

static int	refl_color(t_color *color, int deep)
{
	int	i;

	i = 0;
	while(i < deep)
	{
		color[i + 1].color = parse_color(0, color[i + 1].color, 1 - color[i + 1].reflection) +
			parse_color(0, color[i].color, color[i + 1].reflection);
		i++;
	}
	return (color[i].color);
}

static int	average_color(int *color, int smooth)
{
	int	i;
	int d[3] = {0, 0, 0};

	i = 0;
	while( i < smooth * smooth)
	{
		d[0] += (float)(color[i] / 0x10000 % 256);
		d[1] += (float)(color[i] / 0x100 % 256);
		d[2] += (float)(color[i] % 256);
		i++;
	}
	d[0] /= smooth * smooth;
	d[1] /= smooth * smooth;
	d[2] /= smooth * smooth;
	return (d[0] * 0x10000 + d[1] * 0x100 + d[2]);
}

static int		parse_color_(int c1, unsigned int it)
{
	double			t;
	unsigned char	dr;
	unsigned char	dg;
	unsigned char	db;

	t = (double)c1 / (double)it;
	dr = 9 * (1 - t) * t * t * t * 255;
	dg = 15 * (1 - t) * (1 - t) * t * t * 255;
	db = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (dr * 0x10000 + dg * 0x100 + db);
}
/*
**
***********************************CONVERT**************************************
**
*/
static	void	convert_obj(__constant t_o *o, t_obj *obj, int num)
{
	while (num--)
	{
		obj[num].name = o[num].name;
		obj[num].c = (float3){o[num].c.x, o[num].c.y, o[num].c.z};
		obj[num].d = (float3){o[num].d.x, o[num].d.y, o[num].d.z};
		if (obj[num].name == PLANE)
			obj[num].c = cam_rot(obj[num].d, obj[num].c);
		if (obj[num].name == SPHERE)
			obj[num].c = cam_rot(obj[num].d, obj[num].c);
		obj[num].radius = o[num].radius;
		obj[num].color = o[num].color;
		obj[num].specular = o[num].specular;
		obj[num].reflection = o[num].reflection;
	}
}

static	void	convert_light(__constant t_l *l, t_light *light, int num)
{
	while (num--)
	{
		light[num].type = l[num].type;
		light[num].intensity = l[num].intensity;
		light[num].direction = (float3){l[num].direction.x,
			l[num].direction.y, l[num].direction.z};
	}
}

static	t_scene	convert_scene(t_s s)
{
	t_scene scene;

	scene.o = (float3){s.o.x, s.o.y, s.o.z};
	scene.d = (float3){s.d.x, s.d.y, s.d.z};
	scene.cam_rot = (float3){s.cam_rot.x, s.cam_rot.y, s.cam_rot.z};
	scene.canvas = (float3){s.canvas.x, s.canvas.y, s.canvas.z};
	scene.viewport = (float3){s.viewport.x, s.viewport.y, s.viewport.z};
	scene.t_min = s.t_min;
	scene.t_max = s.t_max;
	scene.n_o = s.n_o;
	scene.n_l = s.n_l;
	return (scene);
}
/*
**
***********************************UTILITY**************************************
**
*/
float3	cam_rot(float3 rot, float3 coord)
{
	float3	angle;
	float3	p[3];
	float	func[6];

	angle.x = PI * rot.x / 180.0f;
	func[0] = cos(angle.x);
	func[1] = sin(angle.x);
	angle.y = PI * rot.y / 180.0f;
	func[2] = cos(angle.y);
	func[3] = sin(angle.y);
	angle.z = PI * rot.z / 180.0f;
	func[4] = cos(angle.z);
	func[5] = sin(angle.z);

	p[0].x = coord.x;
	p[0].y = coord.y * func[0] + coord.z * func[1];
	p[0].z = coord.z * func[0] - coord.y * func[1];

	p[1].x = p[0].x * func[2] + p[0].z * func[3];
	p[1].y = p[0].y;
	p[1].z = p[0].z * func[2] - p[0].x * func[3];

	p[2].x = p[1].x * func[4] + p[1].y * func[5];
	p[2].y = p[1].y * func[4] - p[1].x * func[5];
	p[2].z = p[1].z;
	return (p[2]);
}

float2	q_equation(float k[3])
{
	float2	t;
	float	disc;

	disc = k[1] * k[1] - 4.0f * k[0] * k[2];
	if (disc < 0)
		return ((float2){INFINITY, INFINITY});
	t.x = (-k[1] + sqrt(disc)) / (2.0f * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2.0f * k[0]);
	return (t);
}

float3	v_normal(float3 p, t_closest closest)
{
	float3		proj;
	float3		t;
	float3		n;

	n = p - closest.closest_obj.c;
	if (closest.closest_obj.name == CYLINDER)
	{
		t = (closest.closest_obj.d - closest.closest_obj.c) /
			fast_length(closest.closest_obj.d - closest.closest_obj.c);
		proj = t * dot(n, t);
		n = n - proj;
		n = fast_normalize(n);
		return (n);
	}
	else if(closest.closest_obj.name == CONE)
	{
		t = (closest.closest_obj.d - p) /
			fast_length(closest.closest_obj.d - p);
		proj = t * dot(n, t);
		n = n - proj;
		n = fast_normalize(n);
		return (n);
	}
	else if (closest.closest_obj.name == PLANE || closest.closest_obj.name == DISC)
	{
		n = fast_normalize(-closest.closest_obj.c);
		return (n);
	}
	else if (closest.closest_obj.name == CUBE)
	{
		float3 N[6];
		float NP[6];
		//front side
		t_obj obj = closest.closest_obj;
		float3	P1 = {obj.c.x, obj.c.y, obj.c.z};
		float3	P2 = {obj.c.x, obj.c.y + obj.radius, obj.c.z};
		float3	P3 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
		N[0] = cross(P3 - P1, P2 - P1);
		NP[0] = dot(N[0], p - P1);
		//back side
		N[1] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
		NP[1] = dot(N[1], p - P1);
		//left side
		P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
		P2 = (float3){obj.d.x, obj.d.y + obj.radius, obj.d.z};
		P3 = (float3){obj.c.x, obj.c.y, obj.c.z};
		N[2] = cross(P3 - P1, P2 - P1);
		NP[2] = dot(N[2], p - P1);
		//right side
		N[3] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		NP[3] = dot(N[3], p - P1);
		//down side
		P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
		P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		P3 = (float3){obj.c.x, obj.c.y, obj.c.z};
		N[4] = cross(P3 - P1, P2 - P1);
		NP[4] = dot(N[4], p - P1);
		//up side
		N[5] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.d.x, obj.d.y + obj.radius, obj.d.z};
		NP[5] = dot(N[5], p - P1);

		int i  = -1;
		while (++i < 6)
			if (NP[i] < 5.0F && NP[i] > -5.0f)
				break;
		n = fast_normalize(N[i]);
		return (n);
	}
	else if (closest.closest_obj.name == PIRAMID)
	{
		float3 N[5];
		float NP[5];
		t_obj obj = closest.closest_obj;

		float3	A = obj.d;
		float3	B = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
		float3	C = (A + B) / 2.0F;
		C.y += obj.radius;

		//front side
		float3	P1 = obj.c;
		float3	P3 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
		N[0] = cross(P3 - P1, C - P1);
		NP[0] = dot(N[0], p - P1);
		//back side
		P1 = obj.d;
		P3 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		N[1] = cross(P3 - P1, C - P1);
		NP[1] = dot(N[1], p - P1);
		//left side
		P1 = obj.c;
		P3 = obj.d;
		N[2] = cross(P3 - P1, C - P1);
		NP[2] = dot(N[2], p - P1);
		//right side
		P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		P3 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
		N[3] = cross(P3 - P1, C - P1);
		NP[3] = dot(N[3], p - P1);
		//down side
		P1 = obj.d;
		float3	P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		P3 = obj.c;
		N[4] = cross(P3 - P1, P2 - P1);
		NP[4] = dot(N[4], p - P1);

		int i  = -1;
		while (++i < 5)
			if (NP[i] < 5.0F && NP[i] > -5.0f)
				break;
		n = fast_normalize(N[i]);
		return (n);
	}
	else if (closest.closest_obj.name == TETRAHEDRON)
	{
		float3 N[5];
		float NP[5];
		t_obj obj = closest.closest_obj;

		float3	A = obj.d;
		float3	B = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
		float3	C = (A + B) / 2.0F;
		C.y += obj.radius;

		//front side
		float3	P1 = obj.c;
		float3	P3 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
		N[0] = cross(P3 - P1, C - P1);
		NP[0] = dot(N[0], p - P1);
		//back side
		P1 = obj.d;
		P3 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		N[1] = cross(P3 - P1, C - P1);
		NP[1] = dot(N[1], p - P1);
		//left side
		P1 = obj.c;
		P3 = obj.d;
		N[2] = cross(P3 - P1, C - P1);
		NP[2] = dot(N[2], p - P1);
		//right side
		P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
		P3 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
		N[3] = cross(P3 - P1, C - P1);
		NP[3] = dot(N[3], p - P1);
		//down side
		P1 = obj.c;
		float3	P2 = (float3){obj.c.x + ((obj.d.x - obj.c.x) * 2.0f), obj.c.y, obj.c.z};
		P3 = obj.d;
		N[4] = cross(P3 - P1, P2 - P1);
		NP[4] = dot(N[4], p - P1);

		int i  = -1;
		while (++i < 5)
			if (NP[i] < 5.0F && NP[i] > -5.0f)
				break;
		n = fast_normalize(N[i]);
		return (n);
	}
	else if (closest.closest_obj.name == PARABOLID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		n.x = 2.0F * n.x / coeff.x;
		n.y = -2.0f;
		n.z = 2.0F * n.z / coeff.z;
		n = fast_normalize(n);
		return (n);
	}
	else if (closest.closest_obj.name == HYPERBOLID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		n.x = 2.0F * n.x / coeff.x;
		n.y = -2.0f * n.y / coeff.y;
		n.z = 2.0F * n.z / coeff.z;
		n = fast_normalize(n);
		return (n);
	}
	else if (closest.closest_obj.name == ELLIPSOID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		n.x = 2.0F * n.x / coeff.x;
		n.y = 2.0F * n.y / coeff.y;
		n.z = 2.0F * n.z / coeff.z;
		n = fast_normalize(n);
		return (n);
	}
	n = fast_normalize(n);
	return (n);
}

static float			fix_limits(float3 O, float3 D, float3 Va, t_obj obj, float ints)
{
	float3	Q;
	float3	C = {obj.c.x, obj.c.y, obj.c.z};
	float3	CT = {obj.d.x, obj.d.y, obj.d.z};

	Q = O + D * ints;
	if (dot(Va, Q - CT) < 0 && obj.name == PARABOLID)
		return (ints);
	else if (obj.name == HYPERBOLID)
	{
		float3 P = (C - CT) / fast_length(C - CT) * fast_length(CT - C) + C;
		if (dot((P - C) / fast_length(P - C), Q - P) < 0 && dot(Va, Q - CT) < 0)
			return (ints);
	}
	if (dot(Va, Q - C) > 0 && dot(Va, Q - CT) < 0)
		return (ints);
	return (INFINITY);
}

/*
**
***********************************RAY_OBJ**************************************
**
*/
float2	raysphere(float3 o, float3 d, t_obj obj)
{
	float3	oc;
	float2	t;
	float	k[3];

	oc = o - obj.c;
	k[0] = dot(d, d);
	k[1] = 2.0f * dot(oc, d);
	k[2] = dot(oc, oc) - obj.radius * obj.radius;
	t = q_equation(k);
	return (t);
}

float intersect_cyl_con(float3 d, float3 o, float3 v, t_obj obj, float t)
{
	float3	p;
	float3	a;
	float k[2];

	if (t < 0)
		return (INFINITY);
	p = d * t + o;
	a = p - obj.c;
	k[0] = dot(v, a);
	a = p - obj.d;
	k[1] = dot(v, a);
	if (k[0] > 0 && k[1] < 0 && t > 0)
		return (t);
	return (INFINITY);
}

float2	raycylinder(float3 o, float3 d, t_obj obj)
{
	float3	p;
	float3	v;
	float2	t;
	float3	a[2];
	float	k[3];

	v = (obj.d - obj.c) / fast_length(obj.d - obj.c);
	p = o - obj.c;
	a[0] = d - v * dot(d, v);
	k[0] = dot(a[0], a[0]);
	a[1] = p - v * dot(p, v);
	k[1] = 2.0f * dot(a[0], a[1]);
	k[2] = dot(a[1], a[1]) - obj.radius * obj.radius;
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, v, obj, t.x);
	t.y = intersect_cyl_con(d, o, v, obj, t.y);
	return (t);
}

float2	raycone(float3 o, float3 d, t_obj obj)
{
	float3	p;
	float3	v;
	float2	t;
	float3	a[2];
	float	angle;
	float	k[3];

	angle = PI * obj.radius / 180;
	v = (obj.d - obj.c) / fast_length(obj.d - obj.c);
	p = o - obj.d;
	a[0] = d - v * dot(d, v);
	k[0] = cos(angle) * cos(angle) * dot(a[0], a[0]);
	k[0] -= sin(angle) * sin(angle) * dot(d, v) * dot(d, v);
	a[1] = p - v * dot(p, v);
	k[1] = 2.0f * cos(angle) * cos(angle) * dot(a[0], a[1]);
	k[1] -= 2.0f * sin(angle) * sin(angle) * dot(d, v) * dot(p, v);
	k[2] = cos(angle) * cos(angle) * dot(a[1], a[1]);
	k[2] -= sin(angle) * sin(angle) * dot(p, v) * dot(p, v);
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, v, obj, t.x);
	t.y = intersect_cyl_con(d, o, v, obj, t.y);
	return (t);
}

float2	rayplane(float3 o, float3 d, t_obj obj)
{
	float3	oc;
	float3	n;
	float2	t;
	float	k[2];

	n = -obj.c / fast_length(-obj.c);
	oc = o - obj.c;
	k[0] = dot(d, n);
	k[1] = dot(oc, n);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = INFINITY;
		return (t);
	}
	return ((float2){INFINITY, INFINITY});
}

float2	intersect_ray_ellipsoid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float3	OC;
	float3	C = {obj.c.x, obj.c.y, obj.c.z};

	OC = O - C;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) + (D.y * D.y / coeff.y) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) + (2.0F * OC.y * D.y / coeff.y) + (2.0F * OC.z * D.z / coeff.z);
	k3 =  (OC.x * OC.x / coeff.x) + (OC.y * OC.y / coeff.y) + (OC.z * OC.z / coeff.z) - obj.radius * obj.radius;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	return ((float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)});
}

float2	intersect_ray_paraboloid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float2	T;
	float3	OC;
	float3	C = {obj.c.x, obj.c.y, obj.c.z};
	float3	Va = (obj.d - C) / fast_length(obj.d - C);

	OC = O - C;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) + (2.0F * OC.z * D.z / coeff.z) - D.y;
	k3 =  (OC.x * OC.x / coeff.x) + (OC.z * OC.z / coeff.z) - OC.y;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)};
	T.x = fix_limits(O, D, Va, obj, T.x);
	T.y = fix_limits(O, D, Va, obj, T.y);
	return (T);
}

float2	intersect_ray_hyperbolid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float2	T;
	float3	OC;
	float3	C = {obj.c.x, obj.c.y, obj.c.z};
	float3	CT = {obj.d.x, obj.d.y, obj.d.z};
	float3	Va = (CT - C) / fast_length(CT - C);

	OC = O - C;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) - (D.y * D.y / coeff.y) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) - (2.0F * OC.y * D.y / coeff.y) + (2.0F * OC.z * D.z / coeff.z);
	k3 =  (OC.x * OC.x / coeff.x) - (OC.y * OC.y / coeff.y) + (OC.z * OC.z / coeff.z) - obj.radius;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)};
	T.x = fix_limits(O, D, Va, obj, T.x);
	T.y = fix_limits(O, D, Va, obj, T.y);
	return (T);
}

float2	intersect_ray_disc(float3 O, float3 D, t_obj obj)
{
	float3	C = obj.d;
	float2	T = rayplane(O, D, obj);

	if (T.x != INFINITY)
	{
		float3 P = O + D * T.x;
		float3 PC = P - C;
		float k = dot(PC, PC);
        if (k <= obj.radius * obj.radius)
			return ((float2){T.x, INFINITY});
	}
	return ((float2){INFINITY, INFINITY});
}

static float	intersect_ray_triangle(float3 P1, float3 P2, float3 P3, float3 O, float3 D)
{
	float3 e1 = P2 - P1;
    float3 e2 = P3 - P1;
    float3 pvec = cross(D, e2);
    float det = dot(e1, pvec);

    if (det < 1e-8 && det > -1e-8) {
        return INFINITY;
    }

    float inv_det = 1 / det;
    float3 tvec = O - P1;
    float u = dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return INFINITY;
    }

    float3 qvec = cross(tvec, e1);
    float v = dot(D, qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return INFINITY;
    }
    return dot(e2, qvec) * inv_det;
}

float2	intersect_ray_cube(float3 O, float3 D, t_obj obj)
{
	//front
	float3	P1 = {obj.c.x, obj.c.y, obj.c.z};
	float3	P2 = {obj.c.x, obj.c.y + obj.radius, obj.c.z};
	float3	P3 = {obj.c.x + obj.radius, obj.c.y + obj.radius, obj.c.z};
	float3	P4 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T = intersect_ray_triangle(P1, P2, P4, O, D);
	T == INFINITY ? T = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	//back
	P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
	P2 = (float3){obj.d.x, obj.d.y + obj.radius, obj.d.z};
	P3 = (float3){obj.d.x + obj.radius, obj.d.y + obj.radius, obj.d.z};
	P4 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	float T1 = intersect_ray_triangle(P1, P2, P4, O, D);
	T1 == INFINITY ? T1 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T1 < T ? T = T1 : 0;
	// //left
	P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
	P2 = (float3){obj.d.x, obj.d.y + obj.radius, obj.d.z};
	P3 = (float3){obj.c.x, obj.c.y + obj.radius, obj.c.z};
	P4 = (float3){obj.c.x, obj.c.y, obj.c.z};
	float T2 = intersect_ray_triangle(P1, P2, P4, O, D);
	T2 == INFINITY ? T2 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	// //right
	P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	P2 = (float3){obj.d.x + obj.radius, obj.d.y + obj.radius, obj.d.z};
	P3 = (float3){obj.c.x + obj.radius, obj.c.y + obj.radius, obj.c.z};
	P4 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T3 = intersect_ray_triangle(P1, P2, P4, O, D);
	T3 == INFINITY ? T3 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T3 < T2 ? T2 = T3 : 0;
	// //down
	P1 = (float3){obj.d.x, obj.d.y, obj.d.z};
	P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	P3 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
	P4 = (float3){obj.c.x, obj.c.y, obj.c.z};
	float T4 = intersect_ray_triangle(P1, P2, P4, O, D);
	T4 == INFINITY ? T4 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	// //up
	P1 = (float3){obj.d.x, obj.d.y + obj.radius, obj.d.z};
	P2 = (float3){obj.d.x + obj.radius, obj.d.y + obj.radius, obj.d.z};
	P3 = (float3){obj.c.x + obj.radius, obj.c.y + obj.radius, obj.c.z};
	P4 = (float3){obj.c.x, obj.c.y + obj.radius, obj.c.z};
	float T5 = intersect_ray_triangle(P1, P2, P4, O, D);
	T5 == INFINITY ? T5 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T5 < T4 ? T4 = T5 : 0;

	T2 < T ? T = T2 : 0;
	T4 < T ? T = T4 : 0;
	return ((float2)(T, INFINITY));
}


float2	intersect_ray_piramid(float3 O, float3 D, t_obj obj)
{
	float3	A = obj.d;
	float3	B = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float3	C = (A + B) / 2.0F;
	C.y += obj.radius;
	//front
	float3	P1 = obj.c;
	float3	P2 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T = intersect_ray_triangle(P1, P2, C, O, D);
	//back
	P1 = obj.d;
	P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	float T1 = intersect_ray_triangle(P1, P2, C, O, D);
	T1 < T ? T = T1 : 0;
	// //left
	P1 = obj.d;
	P2 = obj.c;
	float T2 = intersect_ray_triangle(P1, P2, C, O, D);
	// //right
	P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	P2 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T3 = intersect_ray_triangle(P1, P2, C, O, D);
	T3 < T2 ? T2 = T3 : 0;
	// //down
	P1 = obj.d;
	P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	float3	P3 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float3	P4 = obj.c;
	float T4 = intersect_ray_triangle(P1, P2, P4, O, D);
	T4 == INFINITY ? T4 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;

	T2 < T ? T = T2 : 0;
	T4 < T ? T = T4 : 0;
	return ((float2)(T, INFINITY));
}

float2	intersect_ray_tetrahedron(float3 O, float3 D, t_obj obj)
{
	float3	A = obj.d;
	float3	B = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float3	D = (float3){obj.c.x + ((obj.d.x - obj.c.x) * 2.0f), obj.c.y, obj.c.z};
	float3	C = (A + B) / 2.0F;
	C.y += obj.radius;
	//front
	float3	P1 = obj.c;
	float3	P2 = {obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T = intersect_ray_triangle(P1, P2, C, O, D);
	//back
	P1 = obj.d;
	P2 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	float T1 = intersect_ray_triangle(P1, P2, C, O, D);
	T1 < T ? T = T1 : 0;
	// //left
	P1 = obj.d;
	P2 = obj.c;
	float T2 = intersect_ray_triangle(P1, P2, C, O, D);
	// //right
	P1 = (float3){obj.d.x + obj.radius, obj.d.y, obj.d.z};
	P2 = (float3){obj.c.x + obj.radius, obj.c.y, obj.c.z};
	float T3 = intersect_ray_triangle(P1, P2, C, O, D);
	T3 < T2 ? T2 = T3 : 0;
	// //down
	P1 = obj.c;
	P2 = obj.d;
	float3	P3 = D;
	float T4 = intersect_ray_triangle(P1, P2, P3, O, D);

	T2 < T ? T = T2 : 0;
	T4 < T ? T = T4 : 0;
	return ((float2)(T, INFINITY));
}

/*
**
***********************************LIGHT****************************************
**
*/
float	ft_p_d(float3 l, float3 n, float3 v, int s, float intens)
{
	float		rv;
	float		nl;
	float		i;
	float3		r;

	i = 0.0f;
	nl = dot(n, l);
	nl > 0.0f ? i += intens * nl / (fast_length(n) * fast_length(l)) : 0;
	if (s >= 0)
	{
		r = 2.0f * n * dot(n, l) - l;
		rv = dot(r, v);
		rv > 0.0f ? i += intens * pow(rv / (fast_length(r) * fast_length(v)), s) : 0;
	}
	return (i);
}

float3	ft_light_p_d(float3 p, t_light light, t_obj *obj, int n_o, int n_l)
{
	t_closest	closest;
	float		max;
	float3		l;

	if (light.type == POINT)
	{
		l = light.direction - p;
		max = 1.0f;
	}
	else
	{
		l = light.direction;
		max = INFINITY;
	}
	closest = intersections((t_scene){p, l, (float3){0,0,0}, (float3){0,0,0},
		(float3){0,0,0}, 0.001f, max, n_o, n_l}, obj);
	if (closest.closest_obj.color)
		return ((float3){INFINITY, INFINITY, 0});
	return (l);
}

float	ft_light(float3 *pnv, int s, t_light *light, t_obj *obj, int n_o, int n_l)
{
	int			a;
	float		i;
	float3		l;

	i = 0.0f;
	a = -1;
	while (++a < n_l)
	{
		if (light[a].type == AMBIENT)
			i += light[a].intensity;
		else
		{
			l = ft_light_p_d(pnv[0], light[a], obj, n_o, n_l);
			if (l.x != INFINITY && l.y != INFINITY)
				i += ft_p_d(l, pnv[1], pnv[2], s, light[a].intensity);
		}
	}
	i > 1.0f ? i = 1.0f : 0;
	return (i);
}

/*
**
***********************************MAIN*****************************************
**
*/

t_closest	intersections(t_scene scene, t_obj *obj)
{
	t_closest	closest;
	float2		t;
	int			i;

	closest.closest_obj.color = 0;
	closest.c_t = scene.t_max;
	i = -1;
	while (++i < scene.n_o)
	{
		if (obj[i].name == CYLINDER)
			t = raycylinder(scene.o, scene.d, obj[i]);
		else if (obj[i].name == SPHERE)
			t = raysphere(scene.o, scene.d, obj[i]);
		else if (obj[i].name == PLANE)
			t = rayplane(scene.o, scene.d, obj[i]);
		else if (obj[i].name == CONE)
			t = raycone(scene.o, scene.d, obj[i]);
		else if (obj[i].name == ELLIPSOID)
			t = intersect_ray_ellipsoid(scene.o, scene.d, obj[i]);
		else if (obj[i].name == PARABOLID)
			t = intersect_ray_paraboloid(scene.o, scene.d, obj[i]);
		else if (obj[i].name == HYPERBOLID)
			t = intersect_ray_hyperbolid(scene.o, scene.d, obj[i]);
		else if (obj[i].name == DISC)
			t = intersect_ray_disc(scene.o, scene.d, obj[i]);
		else if (obj[i].name == CUBE)
			t = intersect_ray_cube(scene.o, scene.d, obj[i]);
		else if (obj[i].name == PIRAMID)
			t = intersect_ray_piramid(scene.o, scene.d, obj[i]);
		else if (obj[i].name == TETRAHEDRON)
			t = intersect_ray_tetrahedron(scene.o, scene.d, obj[i]);
		if (t.x > scene.t_min && t.x < scene.t_max && t.x < closest.c_t)
		{
			closest.c_t = t.x;
			closest.closest_obj = obj[i];
		}
		if (t.y > scene.t_min && t.y < scene.t_max && t.y < closest.c_t)
		{
			closest.c_t = t.y;
			closest.closest_obj = obj[i];
		}
	}
	return (closest);
}

int	raytrace(t_scene scene, t_obj *obj, t_light *light)
{
	t_color		color[DEEP + 1];
	t_closest	closest;
	float3		p;
	float3		n;
	float3		r;
	int			deep = DEEP;

	while (deep >= 0)
	{
		closest = intersections(scene, obj);
		if (!closest.closest_obj.color)
			return (0);
		p = scene.o + scene.d * closest.c_t;
		n = v_normal(p, closest);
		color[deep].color = parse_color(0, closest.closest_obj.color,
			ft_light((float3[3]){p, n, -scene.d}, closest.closest_obj.specular,
				light, obj, scene.n_o, scene.n_l));
		color[deep].reflection = closest.closest_obj.reflection;
		if (deep > 0 && closest.closest_obj.reflection > 0)
		{
			r = 2.0f * n * dot(n, -scene.d) - -scene.d;
			scene = (t_scene){p, r, scene.cam_rot, scene.canvas, scene.viewport,
				0.001f, INFINITY, scene.n_o, scene.n_l};
			deep--;
		}
		else
			break;
	}
	DEEP ? color[DEEP].color = refl_color(color, DEEP) : 0;
	return (color[DEEP].color);
}

__kernel
void	draw_scene(__global int *buff, t_s s, __constant t_o *o, __constant t_l *l)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			i;
	int			row;
	int			col;
	int			color[4];
	int			smooth;
	t_scene		scene;
	t_light		light[20];
	t_obj		obj[20];

	scene = convert_scene(s);
	convert_obj(o, obj, scene.n_o);
	convert_light(l, light, scene.n_l);

	smooth = 1;
	i = 0;
	row = -1;
	while (++row < smooth)
	{
		col = -1;
		while(++col < smooth)
		{
			scene.d = (float3){(x - scene.canvas.x / 2.0f + (row + 0.5f) / smooth)
				* scene.viewport.x / scene.canvas.x,
			(scene.canvas.y / 2.0f - y + (col + 0.5f) / smooth)
				* scene.viewport.y / scene.canvas.y, 100};
			scene.d = cam_rot(scene.cam_rot, scene.d);
			color[i++] = raytrace(scene, obj, light);
		}
	}
	buff[x + y * (int)scene.canvas.x] = average_color(color, smooth);
}