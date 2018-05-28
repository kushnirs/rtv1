/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/05/22 18:16:17 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_CL_H
# define RTV1_CL_H

# define PI 3.14159265358979323846
# define DEEP 3

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

typedef struct			s_color
{
	int					color;
	float				reflection;
}						t_color;

typedef struct			s_scene
{
	float3				o;
	float3				d;
	float3				cam_rot;
	float3				canvas;
	float3				viewport;
	float				t_min;
	float				t_max;
	int					n_o;
	int					n_l;
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
	t_point				cam_rot;
	t_point				canvas;
	t_point				viewport;
	float				t_min;
	float				t_max;
	int					n_o;
	int					n_l;
}						t_s;

int						raytrace(t_scene scene, t_obj *obj, t_light *light);
float3					v_normal(float3 p, t_closest closest);
t_closest				intersections(t_scene scene, t_obj *obj);
float					ft_light(float3 *pnv, int s, t_light *light, t_obj *obj, int n_o, int n_l);
float3					ft_light_p_d(float3 pnv, t_light light, t_obj *obj, int n_o, int n_l);
float					ft_p_d(float3 l, float3 n, float3 v, int s, float intens);
float3					canvastoviewport(float3 point, t_scene scene);
void					draw_scene(__global int *buff, t_s scene, __constant t_o *obj, __constant t_l *light);
float2					q_equation(float k[3]);
float3					cam_rot(float3 rot, float3 coord);
/*
** ray_obj
*/
float2					raysphere(float3 o, float3 d, t_obj obj);
float					intersect_cyl_con(float3 d, float3 o, float3 v, t_obj obj, float t);
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
