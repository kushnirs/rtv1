/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/03/02 16:22:59 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <OpenCL/opencl.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "ft_printf.h"

# include <stdio.h>

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU
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
	float				t_min;
	float				t_max;
	int					n_o;
	int					n_l;
}						t_scene;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*surface;
	int					*pixel;
	SDL_Event			event;
	t_host				host;
	t_scene				scene;
	t_obj				*obj;
	t_light				*light;
}						t_sdl;

/*
**	main func
*/
void					parse_param(char *filename, t_sdl *data);
void					kernel_param(t_sdl *data);
int						host_fract(char *filename, char *funcname, t_sdl *data);
int						check_float(char *str, float *res);
int						check_coord(char *str, t_point *res);
int						check_int(char *str, int *res);
void					fps(t_sdl *data);
/*
**	color func
*/
int						parse_color(int c1, int c2, float t);
int						parse_color_2(int c1, t_ui t);
int						average_color(int *color, int smooth);
/*
**	handlers
*/

#endif
