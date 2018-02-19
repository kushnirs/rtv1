/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/19 22:25:10 by sergee           ###   ########.fr       */
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
	while (++i < 4)
	{
		if (!ft_strcmp(scene->obj[i].name, "cylinder"))
			t = raycylinder(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "sphere"))
			t = raysphere(scene->o, scene->d, &scene->obj[i]);
		else if (!ft_strcmp(scene->obj[i].name, "plane"))
			t = rayplane(scene->o, scene->d, &scene->obj[i]);
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

static t_point	v_normal(t_point *o, t_point *d, t_point *p, t_closest *closest)
{
	t_point		t;
		t_point		n;
		double		scal;
		t_point		proj;
		
		t = closest->closest_obj->c;
		if (!ft_strcmp(closest->closest_obj->name, "cylinder"))
		{
			n = vector_substr(p, &t);
			scal = vector_scalar(&n, &closest->closest_obj->d) /
				vector_scalar(&closest->closest_obj->d, &closest->closest_obj->d);
			proj = vector_mult(&closest->closest_obj->d, scal);
			n = vector_substr(&n, &proj);
			n = vector_mult(&n, 1 / vector_length(&n));
			return (n);
		}
		else if (!ft_strcmp(closest->closest_obj->name, "plane"))
			return (closest->closest_obj->d);
		n = vector_substr(p, &t);
		n = vector_mult(&n, 1 / vector_length(&n));
		return (n);
}

// static t_point	v_normal(t_point *o, t_point *d, t_point *p, t_closest *closest)
// {
// 	t_point		t;
// 	t_point		n;
// 	t_point		proj;

	
// 	if (!ft_strcmp(closest->closest_obj->name, "sphere"))
// 		t = closest->closest_obj->c;
// 	else if (!ft_strcmp(closest->closest_obj->name, "cylinder"))
// 	{
// 		t = vector_addition(&closest->closest_obj->c, &closest->closest_obj->d);
// 		t = vector_mult(&t, 0.5);
// 	}
// 	if (!ft_strcmp(closest->closest_obj->name, "plane"))
// 		return (closest->closest_obj->d);
// 	n = vector_substr(p, &t);
// 	n = vector_mult(&n, 1 / vector_length(&n));
// 	return (n);
// }

static int	raytrace(t_scene scene)
{
	t_closest	closest;
	t_point		p;
	t_point		n;
	t_point		view;
	int			i;

	t_point		r;
	int			color[2];

	closest = intersections(&scene);
	if (!closest.closest_obj)
		return (0);
	p = vector_addition(scene.o, &((t_point){scene.d->x * closest.c_t,
		scene.d->y * closest.c_t, scene.d->z * closest.c_t}));
	n = v_normal(scene.o, scene.d, &p, &closest);
	view = vector_mult(scene.d, -1);
	color[0] = parse_color(0, closest.closest_obj->color,
		ft_light(&p, &n, &view, closest.closest_obj->specular,
			scene.light, scene.obj));
	// if (deep <= 0 || closest_obj->reflection <= 0)
	// 	return (color[0]);
	// r = reflect_ray(view, pn[1]);
	// color[1] = raytrace(&pn[0], &r, obj, light, deep - 1, 0.001);
	// color[0] = parse_color(0, color[0], 1 - closest_obj->reflection) + parse_color(0, color[1], closest_obj->reflection);
	return (color[0]);
}

static void	draw_scene(t_mlx *data)
{
	int			x;
	int			y;
	int 		color;
	t_point		d;
	t_light		light[3];
	t_obj		obj[4];

	light[0] = (t_light){"ambient", 0.3, (t_point){0, 0, 0}};
	light[1] = (t_light){"point", 0.5, (t_point){200, 200, 175}};
	light[2] = (t_light){"direction", 0.2, (t_point){100, 400, 400}};

	obj[0] = (t_obj){"cylinder", (t_point){0, -100, 400}, (t_point){0, 100, 400}, 90, 0xff0000, 1000, 0.2};
	obj[1] = (t_obj){"sphere", (t_point){200, 0, 400}, (t_point){0, 0, 0}, 100, 0x0000ff, 500, 0.3};
	obj[2] = (t_obj){"sphere",(t_point){-200, 0, 400}, (t_point){0, 0, 0}, 100, 0x00ff00, 1000, 0.4};
	obj[3] = (t_obj){"plane",(t_point){0, -100, 0}, (t_point){0, -99, 0}, 0, 0xffff00, -1, 0};
	x = -1;
	while (++x < data->canvas.x)
	{
		y = -1;
		while (++y < data->canvas.y)
		{
			d = canvastoviewport((t_point){x - data->canvas.x / 2,
				data->canvas.y / 2 - y, 0}, data);
			d = cam_rot((t_point){0, 0, 0}, d);
			color = raytrace((t_scene){&data->camera, &d, obj,
				light, 1, 1, MAX_SIZE});
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
	.camera = (t_point){0, 0, 0}, .d = 40};
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
