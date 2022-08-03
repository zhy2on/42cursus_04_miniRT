/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/03 21:25:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

double	hit_plane_time(t_p3 o, t_vec3 dir, t_p3 p, t_vec3 nv)
{
	double	denom;
	double	pl_time;

	denom = dot(nv, dir);
	if (denom == 0)
		return (INFINITY);
	pl_time = (dot(nv, vsub(p, o))) / denom;
	if (pl_time <= EPSILON)
		return (INFINITY);
	return (pl_time);
}

int	hit_plane(t_ray *ray, t_figures *elem)
{
	double	pl_time;
	t_plane	pl;

	pl = elem->fig.pl;
	pl_time = hit_plane_time(ray->o, ray->dir, pl.p, pl.nv);
	if (ray->hit.time > pl_time)
	{
		ray->hit.time = pl_time;
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
	double	disc;
	double	tmp;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
	{
		root[0] = INFINITY;
		root[1] = INFINITY;
		return ;
	}
	root[0] = (-b - sqrt(disc)) / (2 * a);
	root[1] = (-b + sqrt(disc)) / (2 * a);
	if (root[0] < EPSILON)
		root[0] = INFINITY;
	if (root[1] < EPSILON)
		root[1] = INFINITY;
	if (root[1] < root[0])
	{
		tmp = root[1];
		root[1] = root[0];
		root[0] = tmp;
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
	if (ray->hit.time > time[0])
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, sp.c));
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}

double	hit_cylinder_time(t_ray *ray, t_cylinder cy, double *y)
{
	t_vec3		v[2];
	t_vec3		oc;
	double		dist[2];
	double		time[2];

	oc = vsub(ray->o, cy.c);
	v[0] = vsub(ray->dir, vscale(cy.nv, dot(ray->dir, cy.nv)));
	v[1] = vsub(oc, vscale(cy.nv, dot(oc, cy.nv)));
	solve_quadratic(length_squared(v[0]),
		2 * dot(v[0], v[1]), length_squared(v[1]) - pow(cy.r, 2), time);
	dist[0] = dot(cy.nv, vsub(vscale(ray->dir, time[0]), vscale(oc, -1)));
	dist[1] = dot(cy.nv, vsub(vscale(ray->dir, time[1]), vscale(oc, -1)));
	if (dist[0] >= 0 && dist[0] <= cy.height)
	{
		*y = dist[0];
		return (time[0]);
	}
	if (dist[1] >= 0 && dist[1] <= cy.height)
	{
		*y = dist[1];
		return (time[1]);
	}
	return (INFINITY);
}

double	hit_caps_time(t_ray *ray, t_cylinder cy)
{
	double	time[2];
	int		ret[2];
	t_vec3	v[2];
	t_p3	c2;

	c2 = vadd(cy.c, vscale(cy.nv, cy.height));
	time[0] = hit_plane_time(ray->o, ray->dir, cy.c, cy.nv);
	time[1] = hit_plane_time(ray->o, ray->dir, c2, cy.nv);
	v[0] = vadd(ray->o, vscale(ray->dir, time[0]));
	v[1] = vadd(ray->o, vscale(ray->dir, time[1]));
	ret[0] = (time[0] < INFINITY && distance(v[0], cy.c) <= cy.r);
	ret[1] = (time[1] < INFINITY && distance(v[1], c2) <= cy.r);
	if (!ret[0] && !ret[1])
		return (INFINITY);
	if (ret[0] && !ret[1])
		return (time[0]);
	if (!ret[0] && ret[1])
		return (time[1]);
	if (time[0] < time[1])
		return (time[0]);
	return (time[1]);
}

int	hit_cylinder(t_ray *ray, t_figures *elem)
{
	double		time;
	double		y;
	t_cylinder	cy;

	cy = elem->fig.cy;
	time = hit_cylinder_time(ray, cy, &y);
	if (time < INFINITY && ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point,
					vadd(vscale(cy.nv, y), cy.c)));
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}

int	hit_caps(t_ray *ray, t_figures *elem)
{
	double		time;
	t_cylinder	cy;

	cy = elem->fig.cy;
	time = hit_caps_time(ray, cy);
	if (time < INFINITY && ray->hit.time > time)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, cy.nv) > 0)
			cy.nv = vscale(cy.nv, -1);
		ray->hit.nv = cy.nv;
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}
