/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:30:17 by skushnir          #+#    #+#             */
/*   Updated: 2018/06/01 11:42:21 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <OpenCL/opencl.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "ft_printf.h"
# include "structure.h"

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU
# define B_SIZE	10000
# define S 0
# define L 2
# define O 1

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
int						check_coord(char *str, cl_float3 *res);
int						check_int(char *str, int *res);
/*
**	handlers
*/
int						event(t_sdl *data);
#endif
