/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    mandelbulb.cl                                      :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/05/24 16:18:51 by omiroshn          #+#    #+#              */
/*    Updated: 2018/05/24 16:18:52 by omiroshn         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

static float IterateIntersect(const float3 z0)
{
	float3 z = z0;
	float dr = 1.0f;
	float r = 0.0f;
	float degree = 2.0f;
	for (int i = 0; i < 10 ; i++) {
		r = length(z);
		if (r > 4.0f) break;

		// convert to polar coordinates
		// float theta = asin(z.z/r);
		float theta = acos(z.z/r);
		float phi = atan2(z.y,z.x);
		dr =  pow( r, degree - 1.0f) * degree * dr + 1.0f;

		// scale and rotate the point
		float zr = pow(r, degree);
		theta = theta * degree;
		phi = phi * degree;

		// convert back to cartesian coordinates
		// z = zr * (float3){cos(theta) * cos(phi), cos(phi) * sin(theta), sin(theta)};
		z = zr * (float3){sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta)};
		z +=z0;
	}
	return (0.5f * log(r) * r / dr);
}

float2			intersect_ray_mandelbulb(float3 O, float3 D, t_obj obj)
{
	float totalDistance = 0.0f;
	int steps;
	for (steps = 0; steps < 100; steps++) {
		float3 p = O + totalDistance * D;
		float distance = IterateIntersect(p);
		totalDistance += distance;
		if (distance < 0.0001f) break;
	}
	return ((float2)(1.0f - float(steps) / 100.0f, INFINITY));
}
