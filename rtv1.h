/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/02/19 16:56:57 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "OpenCL/opencl.h"
# include "minilibx/mlx.h"
# include "libft/printf/ft_printf.h"

#include <stdio.h>

# define DEVICE_TYPE CL_DEVICE_TYPE_CPU
# define MAX_SIZE 21474836777
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

typedef	struct			s_kernel
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	com_queue;
	cl_mem				memobj;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		p_id;
	cl_uint				ret_num_dev;
	cl_uint				ret_num_p;
	size_t				gl_w_s;
}						t_host;

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
}						t_point;

typedef struct			s_obj
{
	char				name[10];
	t_point				c;
	t_point				d;
	double				radius;
	int					color;
	int					specular;
	double				reflection;
}						t_obj;

typedef struct			s_light
{
	char				type[15];
	double				intensity;
	t_point				direction;
}						t_light;

typedef struct			s_closest
{
	t_obj		*closest_obj;
	double		c_t;
}						t_closest;

typedef struct			s_scene
{
	t_point	*o;
	t_point	*d;
	t_obj	*obj;
	t_light	*light;
	int		deep;
	double	t_min;
	double	t_max;
}						t_scene;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*image;
	t_point				viewport;
	t_point				canvas;
	t_point				camera;
	t_ui				*data_adr;
	int					bpp;
	int					sl;
	int					endian;
	int					d;
	double				index;
	t_host				host;
}						t_mlx;

int						parse_color(int c1, int c2, double t);
t_ui					parse_color_2(int c1, t_ui t);
int						color_addition(int c1, int c2);
t_point					canvastoviewport(t_point point, t_mlx *data);
double					vector_scalar(t_point *a, t_point *b);
t_point					vector_substr(t_point *a, t_point *b);
t_point					vector_addition(t_point *a, t_point *b);
t_point					vector_mult(t_point *a, double num);
double					vector_length(t_point *a);
int						key_action(int key, t_mlx *data);
int						mouse_menu(int button, int x, int y, t_mlx *data);
t_point					cam_rot(t_point rot, t_point coord);

t_point					raysphere(t_point *o, t_point *d, t_obj *sphere);
t_point					rayplane(t_point *o, t_point *d, t_obj *obj);
t_point					raycylinder(t_point *o, t_point *l, t_obj *sphere);
int						intersect_cylinder(t_point *d, t_point *o, t_point *v, t_obj *obj, t_point *p2, double t);
t_point					reflect_ray(t_point n, t_point l);
t_closest				intersections(t_scene *scene);
double					ft_light(t_point *p, t_point *n, t_point *v, int s, t_light *light, t_obj *obj);


#endif
