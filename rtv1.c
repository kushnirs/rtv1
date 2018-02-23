/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/23 21:16:31 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_closest	intersections(t_scene *scene)
{
	t_closest	closest;
	t_point		t;
	int			i;

	closest.closest_obj = NULL;
	closest.c_t = scene->t_max;
	i = -1;
	while (++i < 8)
	{
		if (!ft_strcmp(scene->obj[i].name, "cylinder"))
			t = raycylinder(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "sphere"))
			t = raysphere(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "plane"))
			t = rayplane(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "cone"))
			t = raycone(scene->o, scene->d, &scene->obj[i]);
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

static t_point	v_normal(t_point *p, t_closest *closest)
{
	double		scal;
	t_point		proj;
	t_point		t;
	t_point		n;
	
	if (!ft_strcmp(closest->closest_obj->name, "cylinder") ||
		!ft_strcmp(closest->closest_obj->name, "cone"))
	{
		t = (t_point){0, 1, 0};
		n = v_sub(p, &closest->closest_obj->c);
		scal = v_scal(&n, &t);
		proj = v_mult(&t, scal);
		n = v_sub(&n, &proj);
		n = v_mult(&n, 1 / v_len(&n));
		return (n);
	}
	else if (!ft_strcmp(closest->closest_obj->name, "plane"))
		return (closest->closest_obj->d);
	n = v_sub(p, &closest->closest_obj->c);
	n = v_mult(&n, 1 / v_len(&n));
	return (n);
}

static int	raytrace(t_scene scene)
{
	int			color[2];
	t_closest	closest;
	t_point		view;
	t_point		p;
	t_point		n;
	t_point		r;

	closest = intersections(&scene);
	if (!closest.closest_obj)
		return (0);
	p = v_add(scene.o, &((t_point){scene.d->x * closest.c_t,
		scene.d->y * closest.c_t, scene.d->z * closest.c_t}));
	n = v_normal(&p, &closest);
	view = v_mult(scene.d, -1);
	color[0] = parse_color(0, closest.closest_obj->color,
		ft_light((t_point[3]){p, n, view}, closest.closest_obj->specular,
			scene.light, scene.obj));
	if (scene.deep <= 0 || closest.closest_obj->reflection <= 0)
		return (color[0]);
	r = reflect_ray(n, view);
	color[1] = raytrace((t_scene){&p, &r, closest.closest_obj, scene.light,
			scene.deep - 1, 0.001, MAX_SIZE});
	color[0] = parse_color(0, color[0], 1 - closest.closest_obj->reflection) +
			parse_color(0, color[1], closest.closest_obj->reflection);
	return (color[0]);
}

static void	draw_scene(t_mlx *data)
{
	int			x;
	int			y;
	int			i;
	double		zoom;
	int			color[1];
	int			smooth;
	t_point		d;
	t_light		light[4];
	t_obj		obj[8];

	light[0] = (t_light){"ambient", 0.2, (t_point){0, 100, 0}};
	light[1] = (t_light){"point", 0.2, (t_point){100, 0, 0}};
	light[3] = (t_light){"point", 0.4, (t_point){-100, 0, 0}};
	light[2] = (t_light){"direction", 0.2, (t_point){0, 199, 200}};
	obj[0] = (t_obj){"cylinder", (t_point){0, -100, 300}, (t_point){0, 50, 300}, 45, 0xff0000, 100, 0.5};
	obj[1] = (t_obj){"sphere", (t_point){100, -50, 200}, (t_point){0, 0, 0}, 50, 0x0000ff, 100, 0.3};
	obj[2] = (t_obj){"cone",(t_point){-100, -100, 200}, (t_point){-100, 50, 200}, 22.5, 0x00ff00, 100, 0.3};
	obj[3] = (t_obj){"plane",(t_point){0, -100, 0}, (t_point){0, 1, 0}, 0, 0xd3d3d3, 500, 0.3};
	obj[4] = (t_obj){"plane",(t_point){0, 0, 700}, (t_point){0, 0, -1}, 0, 0x87ceeb, 300, 0};
	obj[5] = (t_obj){"plane",(t_point){-300, 0, 0}, (t_point){1, 0, 0}, 0, 0x228b22, -1, 0};
	obj[6] = (t_obj){"plane",(t_point){300, 0, 0}, (t_point){-1, 0, 0}, 0, 0xffd700, -1, 0};
	obj[7] = (t_obj){"plane",(t_point){0, 200, 0}, (t_point){0, -1, 0}, 0, 0x8b0a50, -1, 0};
	zoom = 2;
	smooth = 1;
	x = -1;
	while (++x < data->canvas.x)
	{
		y = -1;
		while (++y < data->canvas.y)
		{
			i = 0;
			for (int row = 0; row < smooth; row++)
			{
				for (int col = 0; col < smooth; col++)
				{
					d = canvastoviewport((t_point){zoom * (x - data->canvas.x / 2),
					zoom * (data->canvas.y / 2 - y)}, data);
					d = cam_rot((t_point){0, 0, 0}, d);
					color[0] = raytrace((t_scene){&data->camera, &d, obj,
						light, 1, 1, MAX_SIZE});
				}
			}
			data->data_adr[x + y * (int)data->canvas.x] = color[0];
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
	.camera = (t_point){0, 0, 0}, .d = 100};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.canvas.x, data.canvas.y, "RTv1");
	data.image = mlx_new_image(data.mlx, data.canvas.x, data.canvas.y);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_scene(&data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 6, 0, &preview, &data);
	mlx_hook(data.win, 17, 0, (int (*)())&exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
