/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/02/26 19:45:32 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_CL_H
# define RTV1_CL_H

# include <math.h>
# include "SDL2.framework/Headers/SDL.h"
# include "OpenCL/opencl.h"
# include "minilibx/mlx.h"
# include "libft/printf/ft_printf.h"

#include <stdio.h>

# define DEVICE_TYPE CL_DEVICE_TYPE_CPU
# define B_SIZE	10000
# define S 0
# define L 2
# define O 1
# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4
# define POINT 1
# define DIRECTION 2
# define AMBIENT 3
# define MAX_SIZE 214748367
# define HIGH	1000
# define WIDTH	1000
# define B_A	0
# define B_W	13
# define B_D	2
# define B_S	1
# define B_Q	12
# define B_E	14
# define B_PLUS	69
# define B_MIN	78
# define M_UP	5
# define M_DOWN	4
# define M_L	1
# define M_R	2
# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define ESC	53

typedef	struct			s_host
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	com_queue;
	cl_mem				memobj;
	cl_mem				obj;
	cl_mem				light;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		p_id;
	cl_uint				ret_num_dev;
	cl_uint				ret_num_p;
	size_t				gl_w_s;
}						t_host;

typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_obj
{
	int					name;
	t_point				c;
	t_point				d;
	float				radius;
	int					color;
	float				specular;
	float				reflection;
}						t_obj;

typedef struct			s_light
{
	int					type;
	float				intensity;
	t_point				direction;
}						t_light;

typedef struct			s_closest
{
	t_obj				*closest_obj;
	float				c_t;
}						t_closest;

typedef struct			s_scene
{
	t_point				o;
	t_point				d;
	t_point				cam_rot;
	t_point				canvas;
	t_point				viewport;
	int					deep;
	float				t_min;
	float				t_max;
}						t_scene;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*image;
	t_ui				*data_adr;
	int					bpp;
	int					sl;
	int					endian;
	int					d;
	float				index;
	t_host				host;
	t_scene				scene;
	t_obj				*obj;
	t_light				*light;
}						t_mlx;

void					parse_param(char *filename, t_mlx *data);
void					kernel_param(t_mlx *data);
int						host_fract(char *filename, char *funcname, t_mlx *data);
/*
**	color func
*/
int						parse_color(int c1, int c2, float t);
int						parse_color_2(int c1, t_ui t);
int						average_color(int *color, int smooth);
/*
**	handlers
*/
int						key_action(int key, t_mlx *data);
int						mouse_action(int button, int x, int y, t_mlx *data);

#endif
