/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/02/06 13:52:50 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "OpenCL/opencl.h"
# include "minilibx/mlx.h"
# include "libft/printf/ft_printf.h"

# define DEVICE_TYPE CL_DEVICE_TYPE_CPU
# define MAX_SIZE 2147483647
# define HIGH	1300
# define WIDTH	2000
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

typedef struct			s_sphere
{
	t_point				center;
	double				radius;
	int					color;
}						t_sphere;

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

t_ui					parse_color(int c1, int c2, double t);
t_ui					parse_color_2(int c1, t_ui t);
t_point					canvastoviewport(t_point point, t_mlx *data);
double					scalar(t_point *a, t_point *b);
int						key_action(int key, t_mlx *data);
int						mouse_menu(int button, int x, int y, t_mlx *data);

#endif
