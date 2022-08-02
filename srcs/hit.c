/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/02 20:00:50 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

int	hit_plane(t_ray *ray, t_figures *elem)
{
	double	time;
	double	den;
	t_plane	pl;

	pl = elem->fig.pl;
	den = dot(normalize(ray->dir), pl.nv);
	if (!den)
		return (0);
	time = (dot(vsub(pl.p, ray->o), pl.nv) / den);
	if (ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, pl.nv) > 0)
			pl.nv = vscale(pl.nv, -1);
		ray->hit.nv = pl.nv;
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}

void	solve_quadratic(double a, double b, double c, double root[2])
{
	double	sqrt_discriminant;
	double	tmp[2];

	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
	tmp[0] = (-b - sqrt_discriminant) / (2 * a);
	tmp[1] = (-b + sqrt_discriminant) / (2 * a);
	if (tmp[0] < tmp[1])
	{
		root[0] = tmp[0];
		root[1] = tmp[1];
	}
	else
	{
		root[0] = tmp[1];
		root[1] = tmp[0];
	}
}

int	hit_sphere(t_ray *ray, t_figures *elem)
{
	t_vec3		oc;
	t_sphere	sp;
	double		time[2];

	sp = elem->fig.sp;
	oc = vsub(ray->o, sp.c);
	solve_quadratic(length_squared(ray->dir), 2 * dot(ray->dir, oc),
		length_squared(oc) - pow(sp.r, 2), time);
	if (time[0] < EPSILON)
		time[0] = time[1];
	if (ray->hit.time > time[0] && time[0] > EPSILON)
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, sp.c));
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}

double	cylinder_hit_time(t_ray *ray, t_figures *elem, double *y,
		double time[2])
{
	t_vec3		v[2];
	t_vec3		oc;
	t_cylinder	cy;
	double		dist[2];

	cy = elem->fig.cy;
	oc = vsub(ray->o, cy.c);
	v[0] = vsub(ray->dir, vscale(cy.nv, dot(ray->dir, cy.nv)));
	v[1] = vsub(oc, vscale(cy.nv, dot(oc, cy.nv)));
	solve_quadratic(length_squared(v[0]),
		2 * dot(v[0], v[1]), length_squared(v[1]) - pow(cy.r, 2), time);
	dist[0] = dot(cy.nv, vsub(vscale(ray->dir, time[0]), vscale(oc, -1)));
	dist[1] = dot(cy.nv, vsub(vscale(ray->dir, time[1]), vscale(oc, -1)));
	if (dist[0] >= 0 && dist[0] <= cy.height && time[0] > EPSILON)
	{
		*y = dist[0];
		return (time[0]);
	}
	if (dist[1] >= 0 && dist[1] <= cy.height && time[1] > EPSILON)
	{
		*y = dist[1];
		return (time[1]);
	}
	return (INFINITY);
}

int	hit_cylinder(t_ray *ray, t_figures *elem)
{
	double		time[2];
	double		cy_time;
	double		y;
	t_cylinder	cy;

	cy = elem->fig.cy;
	cy_time = cylinder_hit_time(ray, elem, &y, time);
	if (cy_time < INFINITY && ray->hit.time > cy_time && cy_time > EPSILON)
	{
		ray->hit.time = cy_time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point,
					vadd(vscale(cy.nv, y), cy.c)));
		ray->hit.clr = elem->clr;
	}
	return (cy_time != INFINITY);
}
