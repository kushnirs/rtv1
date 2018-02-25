/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/25 23:23:20 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_cl.h"

int		main(int ac, char **av)
{
	t_mlx	data;

	double		zoom;
	int			smooth;
	t_light		light[4];
	t_obj		obj[8];
	t_scene		scene;

	light[0] = (t_light){AMBIENT, 0.2, (t_point){0, 100, 0}};
	light[1] = (t_light){POINT, 0.2, (t_point){100, 0, 0}};
	light[3] = (t_light){POINT, 0.4, (t_point){-100, 0, 0}};
	light[2] = (t_light){DIRECTION, 0.2, (t_point){0, 199, 200}};
	obj[0] = (t_obj){CYLINDER, (t_point){0, -100, 400}, (t_point){0, 50, 400}, 45, 0xff0000, 100, 0.5};
	obj[1] = (t_obj){SPHERE, (t_point){100, -50, 200}, (t_point){0, 0, 0}, 50, 0x0000ff, 100, 0.3};
	obj[2] = (t_obj){CONE,(t_point){-100, -100, 300}, (t_point){-100, 50, 300}, 22.5, 0x00ff00, 100, 0.3};
	obj[3] = (t_obj){PLANE,(t_point){0, -100, 0}, (t_point){0, 1, 0}, 0, 0xd3d3d3, -1, 0};
	obj[4] = (t_obj){PLANE,(t_point){0, 0, 700}, (t_point){0, 0, -1}, 0, 0x87ceeb, -1, 0};
	obj[5] = (t_obj){PLANE,(t_point){-300, 0, 0}, (t_point){1, 0, 0}, 0, 0x228b22, -1, 0};
	obj[6] = (t_obj){PLANE,(t_point){300, 0, 0}, (t_point){-1, 0, 0}, 0, 0xffd700, -1, 0};
	obj[7] = (t_obj){PLANE,(t_point){0, 200, 0}, (t_point){0, -1, 0}, 0, 0x8b0a50, -1, 0};
	zoom = 2;
	smooth = 2;

	(void)av;
	ac != 1 ? exit(ft_printf("Don't panic! Use main menu:)\n")) : 0;
	data = (t_mlx){.viewport = (t_point){.x = 100, .y = 100}, .canvas = (t_point){.x = WIDTH, .y = HIGH},
	.camera = (t_point){0, 0, -200}, .d = 100};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.canvas.x, data.canvas.y, "RTv1");
	data.image = mlx_new_image(data.mlx, data.canvas.x, data.canvas.y);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	scene = (t_scene){data.camera, (t_point){0,0,0}, data.canvas, data.viewport, 1, 1.0f, MAX_SIZE};
	host_fract("./kernel/rtv1.cl", "draw_scene", &data, &scene, obj, light);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 6, 0, &preview, &data);
	mlx_hook(data.win, 17, 0, (int (*)())&exit, &data);
	mlx_loop(data.mlx);
}