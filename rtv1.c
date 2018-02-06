/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/06 14:01:01 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void	draw_line(t_mlx *data, t_point p0, t_point p1, int color)
{
	double		t;
	double		k;
	double		xy[2];

	k = 1.0 / sqrt((p1.x - p0.x) * (p1.x - p0.x) +\
		(p1.y - p0.y) * (p1.y - p0.y));
	t = 0;
	while (t <= 1)
	{
		xy[0] = p0.x + t * (p1.x - p0.x);
		xy[1] = p0.y + t * (p1.y - p0.y);
		if (xy[0] >= 0 && xy[0] < data->canvas.x &&
			xy[1] >= 0 && xy[1] < data->canvas.y)
			data->data_adr[(int)xy[0] + (int)xy[1] * (int)data->canvas.x] = color;
		t += k;
	}
}

static t_point	raysphere(t_mlx *data,t_point *d, t_sphere *sphere)
{
	t_point	oc;
	t_point t;
	double	disc;
	double	k[3];

	oc = (t_point){data->camera.x - d->x, data->camera.y - d->y, data->camera.z - d->z};
	k[0] = scalar(d, d);
	k[1] = 2 * scalar(&oc, d);
	k[2] = scalar(&oc, &oc) - sphere->radius * sphere->radius;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){1, 1, 0});
	t.x = (-k[1] + sqrt(disc)) / 2 * k[0];
	t.y = (-k[1] - sqrt(disc)) / 2 * k[0];
	return (t);
}

static int	raytrace(t_point *d, t_mlx *data, t_sphere sphere[3])
{
	t_sphere	*closest_sphere;
	t_point		t;
	int			i;
	int			c_t;

	closest_sphere = NULL;
	c_t = MAX_SIZE;
	i = -1;
	while (++i < 3)
	{
		t = raysphere(data, d, &sphere[i]);
		if (t.x > 1 && t.x < MAX_SIZE && t.x < c_t)
		{
			c_t = t.x;
			closest_sphere = &sphere[i];
		}
		if (t.y > 1 && t.y < MAX_SIZE && t.y < c_t)
		{
			c_t = t.y;
			closest_sphere = &sphere[i];
		}
	}
	if (!closest_sphere)
		return (11111);
	return (closest_sphere->color);

}

static void	draw_scene(t_mlx *data)
{
	int		x;
	int		y;
	int 	color;
	t_point	d;
	t_sphere	sphere[3];

	sphere[2] = (t_sphere){(t_point){500, 500, 0}, 10, 0xff0000};
	sphere[1] = (t_sphere){(t_point){510, 510, 0}, 10, 0xffffff};
	sphere[0] = (t_sphere){(t_point){320, 320, 0}, 10, 0xff00ff};
	x = -1;
	while (++x < data->canvas.x)
	{
		y = -1;
		while (++y < data->canvas.y)
		{
			d = canvastoviewport((t_point){x - WIDTH / 2, y - HIGH / 2, 0}, data);
			color = raytrace(&d, data, sphere);
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
	data = (t_mlx){.viewport = (t_point){.x = WIDTH * 20, .y = HIGH * 20}, .canvas = (t_point){.x = WIDTH, .y = HIGH},
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
