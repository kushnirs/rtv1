/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/06/01 11:55:44 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_CL_H
# define RTV1_CL_H

# define PI 3.14159265358979323846
# define M_PI  3.14159265358979323846
# define DEEP 1

typedef float3			cl_float3;

# include "structure.h"

typedef struct			s_color
{
	int					color;
	float				reflection;
}						t_color;

int						raytrace(t_scene scene, __constant t_obj *obj, __constant t_light *light);
float3					v_normal(float3 p, float3 d, t_closest closest);
t_closest				intersections(t_scene scene, __constant t_obj *obj);
float					ft_light(float3 *pnv, int s, __constant t_light *light, __constant t_obj *obj, int n_o, int n_l);
float3					ft_light_p_d(float3 pnv, t_light light, __constant t_obj *obj, int n_o, int n_l);
float					ft_p_d(float3 l, float3 n, float3 v, int s, float intens);
float3					canvastoviewport(float3 point, t_scene scene);
void					draw_scene(__global int *buff, t_scene s, __constant t_obj *o, __constant t_light *l);
float2					q_equation(float k[3]);
float3					cam_rot(float3 rot, float3 coord);
/*
** ray_obj
*/
float2					raysphere(float3 o, float3 d, t_obj obj);
float2					intersect_ray_ellipsoid(float3 O, float3 D, t_obj obj);
float2					intersect_ray_paraboloid(float3 O, float3 D, t_obj obj);
float2					intersect_ray_hyperbolid(float3 O, float3 D, t_obj obj);
float2					intersect_ray_disc(float3 O, float3 D, t_obj obj);
float2					intersect_ray_cube(float3 O, float3 D, t_obj obj);
float2					intersect_ray_piramid(float3 O, float3 D, t_obj obj);
float2					intersect_ray_tetrahedron(float3 O, float3 D, t_obj obj);
float2					raycylinder(float3 o, float3 d, t_obj obj);
float2					raycone(float3 o, float3 d, t_obj obj);
float2					rayplane(float3 o, float3 d, t_obj obj);
#endif
