/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 10:43:59 by sergee            #+#    #+#             */
/*   Updated: 2018/06/01 11:35:50 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

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

# define POINT 1
# define DIRECTION 2
# define AMBIENT 3

typedef struct			s_obj
{
	int					name;
	int					color;
	float				radius;
	float				specular;
	float				reflection;
	cl_float3			c;
	cl_float3			d;
}						t_obj;

typedef struct			s_light
{
	int					type;
	float				intensity;
	cl_float3			direction;
}						t_light;

typedef struct			s_closest
{
	float				c_t;
	t_obj				closest_obj;
}						t_closest;

typedef struct			s_scene
{
	int					n_o;
	int					n_l;
	float				t_min;
	float				t_max;
	cl_float3			o;
	cl_float3			d;
	cl_float3			cam_rot;
	cl_float3			canvas;
	cl_float3			viewport;
}						t_scene;

#endif
