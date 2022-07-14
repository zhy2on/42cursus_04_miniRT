/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 02:57:54 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/15 03:30:17 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "ray.h"
# include "hittable.h"

typedef struct s_sphere_var
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
}			t_sphere_var;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
	t_hit_record	hit_record;
}				t_sphere;

/*
** false 0 true 1
** Find the nearest root that lies in the acceptable range.
*/

int	hit_sphere(t_sphere sphere, t_ray r, double t_min, double t_max, t_hit_record rec)
{
	t_sphere_var	sphere_var;
	t_vec3			outward_normal;

	sphere_var.oc = vsub(r.orig, sphere.center);
	sphere_var.a = length_squared(r.dir);
	sphere_var.half_b = dot(sphere_var.oc, r.dir);
	sphere_var.c = length_squared(sphere_var.oc) - sphere.radius * sphere.radius;
	sphere_var.discriminant = sphere_var.half_b * sphere_var.half_b - sphere_var.a * sphere_var.c;
	if (sphere_var.discriminant < 0)
		return (0);
	sphere_var.sqrtd = sqrt(sphere_var.discriminant);
	sphere_var.root = (-sphere_var.half_b - sphere_var.sqrtd) / sphere_var.a;
	if (sphere_var.root < t_min || t_max < sphere_var.root)
	{
		sphere_var.root = (-sphere_var.half_b + sphere_var.sqrtd) / sphere_var.a;
		if (sphere_var.root < t_min || t_max < sphere_var.root)
			return (0);
	}
	rec.t = sphere_var.root;
	rec.p = ray_at(r, rec.t);
	outward_normal = vdiv_n(vsub(rec.p, sphere.center), sphere.radius);
	set_face_normal(&sphere.hit_record, r, outward_normal);
	return (1);
}

#endif