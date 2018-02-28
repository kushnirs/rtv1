/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/28 13:15:59 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_cl.h"

int		main(int ac, char **av)
{
	t_mlx	data;

	// t_light		light[4];
	// t_obj		obj[8];
	// light[0] = (t_light){AMBIENT, 0.3, (t_point){0, 100, 0}};
	// light[1] = (t_light){POINT, 0.2, (t_point){100, 0, 0}};
	// light[2] = (t_light){POINT, 0.2, (t_point){-100, 0, 0}};
	// light[3] = (t_light){DIRECTION, 0.3, (t_point){100, 100, 0}};
	// obj[0] = (t_obj){CYLINDER, (t_point){0, -100, 400}, (t_point){0, 50, 400}, 45, 0xff0000, 100, 0.5};
	// obj[1] = (t_obj){SPHERE, (t_point){100, -50, 200}, (t_point){0, 0, 0}, 50, 0x0000ff, 100, 0.3};
	// obj[2] = (t_obj){CONE,(t_point){-100, -100, 300}, (t_point){-100, 50, 300}, 22.5, 0x00ff00, 100, 0.3};
	// obj[3] = (t_obj){PLANE,(t_point){0, -100, 0}, (t_point){0, 1, 0}, 0, 0xd3d3d3, -1, 0};
	// obj[4] = (t_obj){PLANE,(t_point){0, 0, 700}, (t_point){0, 0, -1}, 0, 0x87ceeb, -1, 0};
	// obj[5] = (t_obj){PLANE,(t_point){-300, 0, 0}, (t_point){1, 0, 0}, 0, 0x228b22, -1, 0};
	// obj[6] = (t_obj){PLANE,(t_point){300, 0, 0}, (t_point){-1, 0, 0}, 0, 0xffd700, -1, 0};
	// obj[7] = (t_obj){PLANE,(t_point){0, 200, 0}, (t_point){0, -1, 0}, 0, 0x8b0a50, -1, 0};

	// data.scene = (t_scene){(t_point){0, 0, -200}, (t_point){0,0,0}, (t_point){0,0,0},
	// 		(t_point){ WIDTH, HIGH, 0}, (t_point){100, 100, 0}, 1, 1.0f, MAX_SIZE};
	// data.obj = obj;
	// data.light = light;
	ac != 2 ? exit(ft_printf("Usage: ./RTv1 filename\n")) : 0;
	parse_param(av[1], &data);
	// printf("%d\n", data.light[0].type);
	// printf("%f\n", data.light[0].intensity);
	// printf("%f\n", data.light[0].direction.x);
	// printf("%f\n", data.light[0].direction.y);
	// printf("%f\n\n", data.light[0].direction.z);

	// printf("%d\n", data.light[1].type);
	// printf("%f\n", data.light[1].intensity);
	// printf("%f\n", data.light[1].direction.x);
	// printf("%f\n", data.light[1].direction.y);
	// printf("%f\n\n", data.light[1].direction.z);

	// printf("%d\n", data.light[2].type);
	// printf("%f\n", data.light[2].intensity);
	// printf("%f\n", data.light[2].direction.x);
	// printf("%f\n", data.light[2].direction.y);
	// printf("%f\n\n", data.light[2].direction.z);

	// printf("%d\n", data.light[3].type);
	// printf("%f\n", data.light[3].intensity);
	// printf("%f\n", data.light[3].direction.x);
	// printf("%f\n", data.light[3].direction.y);
	// printf("%f\n\n", data.light[3].direction.z);

	// printf("%d\n", data.obj.name);
	// printf("%f\n", data.obj.c.x);
	// printf("%f\n", data.obj.c.y);
	// printf("%f\n", data.obj.c.z);
	// printf("%f\n", data.obj.d.x);
	// printf("%f\n", data.obj.d.y);
	// printf("%f\n", data.obj.d.z);
	// printf("%f\n", data.obj.radius);
	// printf("%d\n", data.obj.color);
	// printf("%f\n", data.obj.specular);
	// printf("%f\n\n", data.obj.reflection);


	// printf("%f\n", data.scene.o.x);
	// printf("%f\n", data.scene.o.y);
	// printf("%f\n", data.scene.o.z);
	// printf("%f\n", data.scene.d.x);
	// printf("%f\n", data.scene.d.y);
	// printf("%f\n", data.scene.d.z);
	// printf("%f\n", data.scene.cam_rot.x);
	// printf("%f\n", data.scene.cam_rot.y);
	// printf("%f\n", data.scene.cam_rot.z);
	// printf("%f\n", data.scene.canvas.x);
	// printf("%f\n", data.scene.canvas.y);
	// printf("%f\n", data.scene.canvas.z);
	// printf("%d\n", data.scene.deep);

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.scene.canvas.x, data.scene.canvas.y, "RTv1");
	data.image = mlx_new_image(data.mlx, data.scene.canvas.x, data.scene.canvas.y);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	host_fract("./kernel/rtv1.cl", "draw_scene", &data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 6, 0, &preview, &data);
	mlx_hook(data.win, 17, 0, (int (*)())&exit, &data);
	mlx_loop(data.mlx);
	return (0);
}