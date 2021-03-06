/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:30:17 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/22 11:41:20 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <OpenCL/opencl.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "ft_printf.h"

# define DEVICE_TYPE CL_DEVICE_TYPE_CPU
# define B_SIZE	10000
# define S 0
# define L 2
# define O 1
# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4
# define ELLIPSOID 5
# define PARABOLID 6
# define HYPERBOLID 7
# define DISC 8
# define CUBE 9
# define PIRAMID 10
# define TETRAHEDRON 11
# define TORUS 12
# define MEBIUS 13
# define MANDELBULB 14

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
	SDL_Surface			*fps;
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
void					fps(t_sdl *data);
int						host_fract(char *filename, char *funcname, t_sdl *data);
int						check_float(char *str, float *res);
int						check_coord(char *str, t_point *res);
int						check_int(char *str, int *res);
/*
**	handlers
*/
int						event(t_sdl *data);
#endif
