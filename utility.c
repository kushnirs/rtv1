/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/02/23 21:11:36 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point	cam_rot(t_point rot, t_point coord)
{
	t_point	p[3];
	double	func[6];

	func[0] = cos(M_PI * rot.x / 180);
	func[1] = sin(M_PI * rot.x / 180);
	func[2] = cos(M_PI * rot.y / 180);
	func[3] = sin(M_PI * rot.y / 180);
	func[4] = cos(M_PI * rot.z / 180);
	func[5] = sin(M_PI * rot.z / 180);
	p[0].x = coord.x;
	p[0].y = coord.y * func[0] + coord.z * func[1];
	p[0].z = coord.z * func[0] - coord.y * func[1];
	p[1].x = p[0].x * func[2] + p[0].z * func[3];
	p[1].y = p[0].y;
	p[1].z = p[0].z * func[2] - p[0].x * func[3];
	p[2].x = p[1].x * func[4] - p[1].y * func[5];
	p[2].y = p[1].x * func[5] + p[1].y * func[4];
	p[2].z = p[1].z;
	return (p[2]);
}

t_point	canvastoviewport(t_point point, t_mlx *data)
{
	t_point	tmp;
	tmp = (t_point){point.x * data->viewport.x / data->canvas.x,
		point.y * data->viewport.y / data->canvas.y, data->d};
	return (tmp);
}

double	formula(double a, double b, double t)
{
	return ((1 - t) * a + b * t);
}

t_point	reflect_ray(t_point n, t_point l)
{
	t_point	r;

	r = v_mult(&n, 2 * v_scal(&n, &l));
	r = v_sub(&r, &l);
	return (r);
}

t_point	q_equation(double k[3])
{
	t_point	t;
	double	disc;

	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
		return ((t_point){MAX_SIZE, MAX_SIZE, 0});
	t.x = (-k[1] + sqrt(disc)) / (2 * k[0]);
	t.y = (-k[1] - sqrt(disc)) / (2 * k[0]);
	return (t);
}
