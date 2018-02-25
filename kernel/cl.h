/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/02/25 23:27:22 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# define MAX_SIZE 214748360
# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4
# define POINT 1
# define DIRECTION 2
# define AMBIENT 3

typedef struct			s_obj
{
	int					name;
	float3				c;
	float3				d;
	float				radius;
	int					color;
	float				specular;
	float				reflection;
}						t_obj;

typedef struct			s_light
{
	int					type;
	float				intensity;
	float3				direction;
}						t_light;

typedef struct			s_closest
{
	t_obj				closest_obj;
	float				c_t;
}						t_closest;

typedef struct			s_scene
{
	float3				o;
	float3				d;
	float3				canvas;
	float3				viewport;
	int					deep;
	float				t_min;
	float				t_max;
}						t_scene;
/*
**	convert
*/
typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_o
{
	int					name;
	t_point				c;
	t_point				d;
	float				radius;
	int					color;
	float				specular;
	float				reflection;
}						t_o;

typedef struct			s_l
{
	int					type;
	float				intensity;
	t_point				direction;
}						t_l;

typedef struct			s_s
{
	t_point				o;
	t_point				d;
	t_point				canvas;
	t_point				viewport;
	int					deep;
	float				t_min;
	float				t_max;
}						t_s;

int						raytrace(t_scene scene, t_obj *obj, t_light *light);
float3					v_normal(float3 p, t_closest closest);
t_closest				intersections(t_scene scene, t_obj *obj);
float					ft_light(float3 *pnv, int s, t_light *light, t_obj *obj);
float3					ft_light_p_d(float3 pnv, t_light light, t_obj *obj);
float					ft_p_d(float3 l, float3 n, float3 v, int s, float intens);
float3					canvastoviewport(float3 point, t_scene scene);
void					draw_scene(__global int *buff, t_s scene, __constant t_o *obj, __constant t_l *light);
float3					q_equation(float k[3]);
/*
** ray_obj
*/
float3					raysphere(float3 o, float3 d, t_obj obj);
float					intersect_cyl_con(float3 d, float3 o, float3 v, t_obj obj, float3 p2, float t);
float3					raycylinder(float3 o, float3 d, t_obj obj);
float3					raycone(float3 o, float3 d, t_obj obj);
float3					rayplane(float3 o, float3 d, t_obj obj);

#endif