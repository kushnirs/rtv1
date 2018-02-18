/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/19 01:14:49 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static t_closest	intersections(t_scene *scene)
{
	t_closest	closest;
	t_point		t;
	int			i;

	closest.closest_obj = NULL;
	closest.c_t = scene->t_min;
	i = -1;
	while (++i < 4)
	{
		if (!ft_strcmp(scene->obj[i].name, "cylinder"))
			t = raycylinder(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "sphere"))
			t = raysphere(scene->o, scene->d, &scene->obj[i]);
		// printf("%.2f-", scene->t_min);
		// printf("%.2f-", t.x);
		// printf("%.2f ", scene->t_max);
		if (t.x > scene->t_min && t.x < scene->t_max && t.x < closest.c_t)
		{
			closest.c_t = t.x;
			closest.closest_obj = &scene->obj[i];
		}
		if (t.y > scene->t_min && t.y < scene->t_max && t.y < closest.c_t)
		{
			closest.c_t = t.y;
			closest.closest_obj = &scene->obj[i];
		}
	}
	return (closest);
}

static double	ft_light(t_point *p, t_point *n, t_point *v, int s, t_light *light, t_obj *obj)
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

t_point	raysphere(t_point *o, t_point *d, t_obj *obj)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = vector_substr(o, &obj->center);
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

static int intersect_cylinder(t_point *d, t_point *o, t_point *v, t_obj *obj, t_point *p2, double t)
{
	t_point	p;
	t_point	a;
	t_point	b;
	double k[2];

	if (k < 0)
		return (0);
	p = vector_mult(d, t);
	p = vector_addition(o, &p);
	a = vector_substr(&p, &obj->center);
	k[0] = vector_scalar(v, &a);
	b = vector_substr(&p, p2);
	k[1] = vector_scalar(v, &b);
	if ((k[0] < 0 && k[1] > 0))
		return (1);
	return (0);
}

t_point	raycylinder(t_point *o, t_point *d, t_obj *obj)
{
	t_point	p;
	t_point	p2;
	t_point	v;
	t_point t;
	t_point	a;
	t_point	b;
	double	disc;
	double	k[3];

	p2 = (t_point){obj->center.x, obj->center.y + 200, obj->center.z};
	v = vector_substr(&obj->center, &p2);
	v = vector_mult(&v, 1 / vector_length(&v));
	p = vector_substr(o, &obj->center);
	a = vector_mult(&v, vector_scalar(d, &v));
	a = vector_substr(d, &a);
	k[0] = vector_scalar(&a, &a);
	b = vector_mult(&v, vector_scalar(&p, &v));
	b = vector_substr(&p, &b);
	k[1] = 2 * vector_scalar(&a, &b);
	k[2] = vector_scalar(&b, &b) - obj->radius * obj->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);

	k[0] = intersect_cylinder(d, o, &v, obj, &p2, t.x);
	k[1] = intersect_cylinder(d, o, &v, obj, &p2, t.y);
	if (k[0] || k[1])
		return (t);
	return ((t_point){MAX_SIZE, MAX_SIZE, 0});
}

static int	raytrace(t_scene scene)
{
	t_closest	closest;
	t_point		t;
	t_point		pn[2];
	t_point		view;
	int			i;

	t_point		r;
	int			color[2];

	closest = intersections(&scene);
	if (!closest.closest_obj)
		return (0);
	// pn[0] = vector_addition(scene.o, &((t_point){scene.d->x * closest.c_t, scene.d->y * closest.c_t, scene.d->z * closest.c_t}));
	// pn[1] = vector_substr(&pn[0], &closest.closest_obj->center);
	// pn[1] = vector_mult(&pn[1], 1 / vector_length(&pn[1]));
	// view = vector_mult(scene.d, -1);
	// color[0] = parse_color(0, closest.closest_obj->color, ft_light(&pn[0], &pn[1], &view, closest.closest_obj->specular, scene.light, scene.obj));
	// if (deep <= 0 || closest_obj->reflection <= 0)
	// 	return (color[0]);
	// r = reflect_ray(view, pn[1]);
	// color[1] = raytrace(&pn[0], &r, obj, light, deep - 1, 0.001);
	// color[0] = parse_color(0, color[0], 1 - closest_obj->reflection) + parse_color(0, color[1], closest_obj->reflection);
	return (closest.closest_obj->color);
}

static void	draw_scene(t_mlx *data)
{
	int			x;
	int			y;
	int 		color;
	t_point		d;
	t_light		light[3];
	t_obj		obj[4];

	light[0] = (t_light){"ambient", 0.2, (t_point){0, 0, 0}};
	light[1] = (t_light){"point", 0.6, (t_point){200, 100, 0}};
	light[2] = (t_light){"direction", 0.2, (t_point){100, 400, 400}};
	// obj[0] = (t_obj){(t_point){0, -100, 300}, 100, 0xff0000, 500, 0.2};
	obj[0] = (t_obj){"cylinder", (t_point){0, -100, 400}, 90, 0, 0xff0000, 500, 0.2};
	obj[1] = (t_obj){"sphere", (t_point){200, 0, 400}, 100, 0, 0x0000ff, 500, 0.3};
	obj[2] = (t_obj){"sphere",(t_point){-200, 0, 400}, 100, 0, 0x00ff00, 10, 0.4};
	obj[3] = (t_obj){"sphere",(t_point){0, -500100, 0}, 500000, 0, 0xffff00, 1000, 0.5};
	x = -1;
	while (++x < data->canvas.x)
	{
		y = -1;
		while (++y < data->canvas.y)
		{
			d = canvastoviewport((t_point){x - data->canvas.x / 2, data->canvas.y / 2 - y, 0}, data);
			d = cam_rot((t_point){0, 0, 0}, d);
			color = raytrace((t_scene){&data->camera, &d, obj, light, 1, 1, MAX_SIZE});
			data->data_adr[x + y * (int)data->canvas.x] = color;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int		main(int ac, char **av)
{
	t_mlx	data;

	(void)av;
	ac != 1 ? exit(ft_printf("Don't panic! Use main menu:)\n")) : 0;
	data = (t_mlx){.viewport = (t_point){.x = 100, .y = 100}, .canvas = (t_point){.x = WIDTH, .y = HIGH},
	.camera = (t_point){0, 0, 0}, .d = 70};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.canvas.x, data.canvas.y, "RTv1");
	data.image = mlx_new_image(data.mlx, data.canvas.x, data.canvas.y);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_scene(&data);
	// mlx_mouse_hook(data.win, &mouse_menu, &data);
	mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 6, 0, &preview, &data);
	mlx_hook(data.win, 17, 0, (int (*)())&exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
