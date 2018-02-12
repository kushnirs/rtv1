/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/12 12:39:37 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static int	ft_check_shadow(double t_max, t_point *p, t_point *l, t_sphere *sphere)
{
	t_sphere	*closest_sphere;
	t_point		t;
	int			i;
	double		c_t;

	closest_sphere = NULL;
	c_t = MAX_SIZE;
	i = -1;
	while (++i < 4)
	{
		t = raysphere(p, l, &sphere[i]);
		if (t.x > 0.001 && t.x < t_max && t.x < c_t)
		{
			c_t = t.x;
			closest_sphere = &sphere[i];
		}
		if (t.y > 0.001 && t.y < t_max && t.y < c_t)
		{
			c_t = t.y;
			closest_sphere = &sphere[i];
		}
	}
	if (!closest_sphere)
		return (0);
	return (1);
}

static double	ft_light(t_point *p, t_point *n, t_point *v, int s, t_light *light, t_sphere *sphere)
{
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
			if (ft_check_shadow(t_max, p, &l, sphere))
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

t_point	raysphere(t_point *o, t_point *d, t_sphere *sphere)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = vector_substr(o, &sphere->center);
	k[0] = vector_scalar(d, d);
	k[1] = 2 * vector_scalar(&oc, d);
	k[2] = vector_scalar(&oc, &oc) - sphere->radius * sphere->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);
	return (t);
}

static int	raytrace(t_point *o, t_point *d, t_sphere *sphere, t_light *light, int deep, double t_min)
{
	t_sphere	*closest_sphere;
	t_point		t;
	t_point		pn[2];
	t_point		view;
	int			i;
	double		c_t;

	t_point		r;
	int			color[2];


	closest_sphere = NULL;
	c_t = MAX_SIZE;
	i = -1;
	while (++i < 4)
	{
		t = raysphere(o, d, &sphere[i]);
		if (t.x > t_min && t.x < MAX_SIZE && t.x < c_t)
		{
			c_t = t.x;
			closest_sphere = &sphere[i];
		}
		if (t.y > t_min && t.y < MAX_SIZE && t.y < c_t)
		{
			c_t = t.y;
			closest_sphere = &sphere[i];
		}
	}
	if (!closest_sphere)
		return (0);
	pn[0] = vector_addition(o, &((t_point){d->x * c_t, d->y * c_t, d->z * c_t}));
	pn[1] = vector_substr(&pn[0], &closest_sphere->center);
	pn[1] = vector_mult(&pn[1], 1 / vector_length(&pn[1]));
	view = vector_mult(d, -1);
	color[0] = parse_color(0, closest_sphere->color, ft_light(&pn[0], &pn[1], &view, closest_sphere->specular, light, sphere));
	if (deep <= 0 || closest_sphere->reflection <= 0)
		return (color[0]);
	r = reflect_ray(view, pn[1]);
	color[1] = raytrace(&pn[0], &r, sphere, light, deep - 1, 0.001);
	color[0] = parse_color(0, color[0], 1 - closest_sphere->reflection) + parse_color(0, color[1], closest_sphere->reflection);
	return (color[0]);
}

static void	draw_scene(t_mlx *data)
{
	int			x;
	int			y;
	int 		color;
	t_point		d;
	t_light		light[3];
	t_sphere	sphere[4];

	light[0] = (t_light){"ambient", 0.2, (t_point){0, 0, 0}};
	light[1] = (t_light){"point", 0.6, (t_point){2, 1, 0}};
	light[2] = (t_light){"direction", 0.2, (t_point){1, 4, 4}};
	sphere[0] = (t_sphere){(t_point){0, -1, 3}, 1, 0xff0000, 500, 0.2};
	sphere[1] = (t_sphere){(t_point){2, 0, 4}, 1, 0x0000ff, 500, 0.3};
	sphere[2] = (t_sphere){(t_point){-2, 0, 4}, 1, 0x00ff00, 10, 0.4};
	sphere[3] = (t_sphere){(t_point){0, -5001, 0}, 5000, 0xffff00, 1000, 0.5};
	x = -1;
	while (++x < data->canvas.x)
	{
		y = -1;
		while (++y < data->canvas.y)
		{
			d = canvastoviewport((t_point){x - data->canvas.x / 2, data->canvas.y / 2 - y, 0}, data);
			color = raytrace(&data->camera, &d, sphere, light, 1, 1);
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
	data = (t_mlx){.viewport = (t_point){.x = 1, .y = 1}, .canvas = (t_point){.x = WIDTH, .y = HIGH},
	.camera = (t_point){0, 0, 0}, .d = 1};
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
