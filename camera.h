/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 02:21:50 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 02:50:14 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"

enum e_cam {
	VIEWPORT_RATIO = 16 / 9,
	VIEWPORT_H = 2,
	VIEWPORT_W = VIEWPORT_H * VIEWPORT_RATIO,
	SAMPLES_PER_PIXEL = 100,
	FOCAL_LENGTH = 1
};

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lower_left_corner;
}			t_cam;

t_cam	init_cam(void)
{
	t_cam	cam;
	t_vec3	vec;

	cam.origin = set_vec3(0, 0, 0);
	cam.horizontal = set_vec3(VIEWPORT_W, 0, 0);
	cam.vertical = set_vec3(0, VIEWPORT_H, 0);
	cam.lower_left_corner = vsub(cam.origin, vdiv_n(cam.horizontal, 2));
	cam.lower_left_corner = vsub(cam.lower_left_corner,
			vdiv_n(cam.vertical, 2));
	vec = set_vec3(0, 0, FOCAL_LENGTH);
	cam.lower_left_corner = vsub(cam.lower_left_corner, vec);
	return (cam);
}

t_ray	get_ray(t_cam cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam.origin;
	ray.dir = vsub(
			vadd(cam.lower_left_corner,
				vadd(vmul_n(cam.horizontal, u), vmul_n(cam.vertical, v))),
			cam.origin);
	return (ray);
}

#endif