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

#include "cl.h"
/*
**
**	CONVERT
**
*/
static	void	convert_obj(__constant t_o *o, t_obj *obj, int num)
{
	while (num--)
	{
		obj[num].name = o[num].name;
		obj[num].c = (float3){o[num].c.x, o[num].c.y, o[num].c.z};
		obj[num].d = (float3){o[num].d.x, o[num].d.y, o[num].d.z};
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
	scene.canvas = (float3){s.canvas.x, s.canvas.y, s.canvas.z};
	scene.viewport = (float3){s.viewport.x, s.viewport.y, s.viewport.z};
	scene.deep = s.deep;
	scene.t_min = s.t_min;
	scene.t_max = s.t_max;
	return (scene);
}
/*
**
**	UTILITY
**
*/
static float3	reflect_ray(float3 n, float3 l)
{
	float3	r;
	r = 2.0f * n * dot(n, l) - l; 
	return (r);
}

static float3	cam_rot(float3 rot, float3 coord)
{
	float3	p[3];
	float	func[6];

	func[0] = cos(M_PI * rot.x / 180);
	func[1] = sin(M_PI * rot.x / 180);
	func[2] = cos(M_PI * rot.y / 180);
	func[3] = sin(M_PI * rot.y / 180);
	func[4] = cos(M_PI * rot.z / 180);
	func[5] = sin(M_PI * rot.z / 180);
	p[0].x = coord.x;
	p[0].y = coord.y * func[0] + coord.z * func[1];
	p[0].z = coord.z * func[0] - coord.y * func[1];
	p[1].x = p[0].x * func[2] + p[0].z * func[3];
	p[1].y = p[0].y;
	p[1].z = p[0].z * func[2] - p[0].x * func[3];
	p[2].x = p[1].x * func[4] - p[1].y * func[5];
	p[2].y = p[1].x * func[5] + p[1].y * func[4];
	p[2].z = p[1].z;
	return (p[2]);
}

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

float3	q_equation(float k[3])
{
	float3	t;
	float	disc;

	disc = k[1] * k[1] - 4.0f * k[0] * k[2];
	if (disc < 0)
		return ((float3){MAX_SIZE, MAX_SIZE, 0});
	t.x = (-k[1] + sqrt(disc)) / (2.0f * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2.0f * k[0]);
	return (t);
}

float3	canvastoviewport(float3 point, t_scene scene)
{
	float3	tmp;
	tmp = (float3){point.x * scene.viewport.x / scene.canvas.x,
		point.y * scene.viewport.y / scene.canvas.y, 100};
	return (tmp);
}

float3	v_normal(float3 p, t_closest closest)
{
	float		scal;
	float3		proj;
	float3		t = {0.0f, 1.0f, 0.0f};
	float3		n;
	
	if (closest.closest_obj.name == CYLINDER || closest.closest_obj.name == CONE)
	{
		n = p - closest.closest_obj.c;
		scal = dot(n, t);
		proj = t * scal;
		n = n - proj;
		n = n / length(n);
		return (n);
	}
	else if (closest.closest_obj.name == PLANE)
		return (closest.closest_obj.d);
	n = p - closest.closest_obj.c;
	n = n / length(n);
	return (n);
}
/*
**
**	RAY_OBJ
**
*/

float3	raysphere(float3 o, float3 d, t_obj obj)
{
	float3	oc;
	float3	t;
	float	disc;
	float	k[3];

	oc = o - obj.c;
	k[0] = dot(d, d);
	k[1] = 2.0f * dot(oc, d);
	k[2] = dot(oc, oc) - obj.radius * obj.radius;
	t = q_equation(k);
	return (t);
}

float intersect_cyl_con(float3 d, float3 o, float3 v, t_obj obj, float3 p2, float t)
{
	float3	p;
	float3	a;
	float k[2];

	if (t < 0)
		return (MAX_SIZE);
	p = d * t;
	p = o + p;
	a = p - obj.c;
	k[0] = dot(v, a);
	a = p - p2;
	k[1] = dot(v, a);
	if (k[0] > 0 && k[1] < 0 && t > 0)
		return (t);
	return (MAX_SIZE);
}

float3	raycylinder(float3 o, float3 d, t_obj obj)
{
	float3	p;
	float3	v;
	float3	t;
	float3	a[2];
	float	k[3];

	v = obj.d - obj.c;
	v = v / length(v);
	p = o - obj.c;
	a[0] = v * dot(d, v);
	a[0] = d - a[0];
	k[0] = dot(a[0], a[0]);
	a[1] = v * dot(p, v);
	a[1] = p - a[1];
	k[1] = 2.0f * dot(a[0], a[1]);
	k[2] = dot(a[1], a[1]) - obj.radius * obj.radius;
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, v, obj, obj.d, t.x);
	t.y = intersect_cyl_con(d, o, v, obj, obj.d, t.y);
	return (t);
}

float3	raycone(float3 o, float3 d, t_obj obj)
{
	float3	p;
	float3	v;
	float3	t;
	float3	a[2];
	float	angle;
	float	k[3];

	angle = M_PI * obj.radius / 180;
	v = obj.d - obj.c;
	v = v / length(v);
	p = o - obj.d;
	a[0] = v * dot(d, v);
	a[0] = d - a[0];
	k[0] = cos(angle) * cos(angle) * dot(a[0], a[0]);
	k[0] -= sin(angle) * sin(angle) * dot(d, v) * dot(d, v);
	a[1] = v * dot(p, v);
	a[1] = p - a[1];
	k[1] = 2.0f * cos(angle) * cos(angle) * dot(a[0], a[1]);
	k[1] -= 2.0f * sin(angle) * sin(angle) * dot(d, v) * dot(p, v);
	k[2] = cos(angle) * cos(angle) * dot(a[1], a[1]);
	k[2] -= sin(angle) * sin(angle) * dot(p, v) * dot(p, v);
	t = q_equation(k);
	t.x = intersect_cyl_con(d, o, v, obj, obj.d, t.x);
	t.y = intersect_cyl_con(d, o, v, obj, obj.d, t.y);
	return (t);
}

float3	rayplane(float3 o, float3 d, t_obj obj)
{
	float3	oc;
	float3	t;
	float	k[2];

	oc = o - obj.c;
	k[0] = dot(d, obj.d);
	k[1] = dot(oc, obj.d);
	if (k[0])
	{
		t.x = -k[1] / k[0];
		t.y = MAX_SIZE;
		return (t);		
	}
	return ((float3){MAX_SIZE, MAX_SIZE, 0});
}
/*
**
**	LIGHT
**
*/

float	ft_p_d(float3 l, float3 n, float3 v, int s, float intens)
{
	float		rv;
	float		nl;
	float		i;
	float3		r;

	i = 0;
	nl = dot(n, l);
	nl > 0 ? i += intens * nl / (length(n) * length(l)) : 0;
	if (s >= 0)
	{
		r = reflect_ray(n, l);
		rv = dot(r, v);
		rv > 0 ? i += intens * pow(rv / (length(r) * length(v)), s) : 0;
	}
	return (i);
}

float3	ft_light_p_d(float3 pnv, t_light light, t_obj *obj)
{
	t_closest	closest;
	float		max;
	float3		l;

	if (light.type == POINT)
	{
		l = light.direction - pnv;
		max = 1.0f;
	}
	else
	{
		l = light.direction;
		max = MAX_SIZE;
	}
	closest = intersections((t_scene){pnv, l, l, l, 0, 0.001, max}, obj);
	if (closest.closest_obj.color)
		return ((float3){MAX_SIZE, MAX_SIZE, 0});
	return (l);
}

float	ft_light(float3 *pnv, int s, t_light *light, t_obj *obj)
{
	int			a;
	float		i;
	float3		l;

	i = 0.0f;
	a = -1;
	while (++a < 4)
	{
		if (light[a].type == AMBIENT)
			i += light[a].intensity;
		else
		{
			l = ft_light_p_d(pnv[0], light[a], obj);
			if (l.x != MAX_SIZE && l.y != MAX_SIZE)
				i += ft_p_d(l, pnv[1], pnv[2], s, light[a].intensity);
		}
	}
	i > 1 ? i = 1 : 0;
	return (i);
}
/*
**
**	MAIN
**
*/

t_closest	intersections(t_scene scene, t_obj *obj)
{
	t_closest	closest;
	float3		t;
	int			i;

	closest.closest_obj.color = 0;
	closest.c_t = scene.t_max;
	i = -1;
	while (++i < 8)
	{
		if (obj[i].name == CYLINDER)
			t = raycylinder(scene.o, scene.d, obj[i]);
		else if (obj[i].name == SPHERE)
			t = raysphere(scene.o, scene.d, obj[i]);
		else if (obj[i].name == PLANE)
			t = rayplane(scene.o, scene.d, obj[i]);
		else if (obj[i].name == CONE)
			t = raycone(scene.o, scene.d, obj[i]);
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
	int			color[2];
	t_closest	closest;
	float3		p;
	float3		n;
	float3		r;

	closest = intersections(scene, obj);
	if (!closest.closest_obj.color)
		return (0);
	p = scene.o + scene.d * closest.c_t;
	n = v_normal(p, closest);
	color[0] = parse_color(0, closest.closest_obj.color,
		ft_light((float3[3]){p, n, -scene.d}, closest.closest_obj.specular,
			light, obj));
	if (scene.deep <= 0 || closest.closest_obj.reflection <= 0)
		return (color[0]);
	r = reflect_ray(n, -scene.d);
	color[1] = raytrace((t_scene){p, r, scene.canvas, scene.viewport,
			scene.deep - 1, 0.001, MAX_SIZE}, obj, light);
	color[0] = parse_color(0, color[0], 1 - closest.closest_obj.reflection) +
			parse_color(0, color[1], closest.closest_obj.reflection);
	return (color[0]);
}

__kernel
void	draw_scene(__global int *buff, t_s s, __constant t_o *o, __constant t_l *l)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			i;
	int			color[4];
	int			smooth;
	t_scene		scene;
	t_light		*light;
	t_obj		*obj;

	obj = (t_obj*)malloc(sizeof(t_obj) * 8);
	light = (t_light*)malloc(sizeof(t_light) * 4);
	scene = convert_scene(s);
	convert_obj(o, obj, 8);
	convert_light(l, light, 4);

	smooth = 2;
	i = 0;
	for (int row = 0; row < smooth; row++)
	{
		for (int col = 0; col < smooth; col++)
		{
			scene.d = canvastoviewport((float3){x - scene.canvas.x / 2.0f + (row + 0.5f) / smooth,
			scene.canvas.y / 2.0f - y + (col + 0.5f) / smooth, 0}, scene);
			scene.d = cam_rot((float3){0, 0, 0}, scene.d);
			color[i++] = raytrace(scene, obj, light);
		}
	}
	buff[x + y * (int)scene.canvas.x] = average_color(color, smooth);
}
