/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:14:49 by sergee            #+#    #+#             */
/*   Updated: 2018/05/08 16:36:19 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define MAX_SOURCE_SIZE 25000
#define CL_BUILD_PROGRAM_FAILURE -11

void		kernel_param(t_sdl *data)
{
	cl_int ret;

	(ret = clSetKernelArg(data->host.kernel, 0, sizeof(cl_mem),
	(void *)&data->host.memobj)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 1, sizeof(t_scene),
		(void *)&data->scene)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 2, sizeof(cl_mem),
	(void *)&data->host.obj)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 3, sizeof(cl_mem),
	(void *)&data->host.light)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	ret = clEnqueueNDRangeKernel(data->host.com_queue, data->host.kernel,
		2, NULL, (size_t[3]){data->surface->w, data->surface->h, 0},
		NULL, 0, NULL, NULL);
	ret ? exit(ft_printf("clEnqueueNDRangeKernel Failed\n")) : 0;
	ret = clEnqueueReadBuffer(data->host.com_queue, data->host.memobj, CL_TRUE,
		0, data->surface->w * data->surface->h * sizeof(int),
		(int*)data->surface->pixels, 0, NULL, NULL);
	ret ? exit(ft_printf("clEnqueueReadBuffer Failed\n")) : 0;
}

static void	host_program(char *funcname, char *str, int size, t_sdl *data)
{
	cl_int	ret;

	data->host.com_queue = clCreateCommandQueue(data->host.context,
		data->host.dev_id, 0, &ret);
	ret ? exit(ft_printf("clCreateCommandQueue Failed\n")) : 0;
	data->host.memobj = clCreateBuffer(data->host.context, CL_MEM_READ_WRITE,
		data->surface->w * data->surface->h * sizeof(int), NULL, &ret);
	ret ? exit(ft_printf("clCreateBuffer Failed\n")) : 0;
	data->host.obj = clCreateBuffer(data->host.context, CL_MEM_USE_HOST_PTR,
		sizeof(t_obj) * data->scene.n_o, data->obj, &ret);
	ret ? exit(ft_printf("clCreateObj Failed\n")) : 0;
	data->host.light = clCreateBuffer(data->host.context, CL_MEM_USE_HOST_PTR,
		sizeof(t_light) * data->scene.n_l, data->light, &ret);
	ret ? exit(ft_printf("clCreateLight Failed\n")) : 0;
	data->host.program = clCreateProgramWithSource(data->host.context, 1,
		(const char **)&str, (const size_t *)&size, &ret);
	ret ? exit(ft_printf("clCreateProgramWithSource Failed\n")) : 0;
	(ret = clBuildProgram(data->host.program, 1, &data->host.dev_id,
	"-I ./kernel", NULL, NULL));
	if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
	   	size_t log_size;
	   	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	   	char *log = (char *) malloc(log_size);
	   	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
		CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	   	printf("%s\n", log);
	}
	ret ? ft_printf("%dBuildProgram Failed\n", ret) : 0;
	data->host.kernel = clCreateKernel(data->host.program, funcname, &ret);
	ret ? exit(ft_printf("clCreateKernel Failed\n")) : 0;
}

int			host_fract(char *filename, char *funcname, t_sdl *data)
{
	int		fp;
	int		size;
	char	*str;
	cl_int	ret;

	(fp = open(filename, O_RDONLY)) <= 0 ?
		exit(ft_printf("Failed to load kernel.\n")) : 0;
	!(str = (char*)malloc(MAX_SOURCE_SIZE)) ?
		exit(ft_printf("Can't allocate memory\n")) : 0;
	(size = read(fp, str, MAX_SOURCE_SIZE)) <= 0 ?
		exit(ft_printf("Can't read file\n")) : 0;
	close(fp);
	(ret = clGetPlatformIDs(1, &data->host.p_id, &data->host.ret_num_p)) ?
		exit(ft_printf("clGetPlatformIDs Failed\n")) : 0;
	ret = clGetDeviceIDs(data->host.p_id, DEVICE_TYPE, 1,
		&data->host.dev_id, &data->host.ret_num_dev);
	ret ? exit(ft_printf("clGetPlatformIDs Failed\n")) : 0;
	data->host.context = clCreateContext(NULL, 1,
		&data->host.dev_id, NULL, NULL, &ret);
	ret ? exit(ft_printf("clCreateContext Failed\n")) : 0;
	host_program(funcname, str, size, data);
	ft_memdel((void**)&str);
	return (0);
}
/*
** if (ret == CL_BUILD_PROGRAM_FAILURE)
** {
**    	size_t log_size;
**    	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
**		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
**    	char *log = (char *) malloc(log_size);
**    	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
**		CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
**    	printf("%s\n", log);
** }
*/
