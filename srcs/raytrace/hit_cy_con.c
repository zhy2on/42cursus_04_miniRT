/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_con.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:14:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 17:17:20 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_cylinder_time(t_ray ray, t_cylinder cy, double *y)
{
	t_vec3		v[2];
	t_vec3		oc;
	double		dist[2];
	double		time[2];

	oc = vsub(ray.o, cy.c);
	v[0] = vsub(ray.dir, vscale(cy.nv, dot(ray.dir, cy.nv)));
	v[1] = vsub(oc, vscale(cy.nv, dot(oc, cy.nv)));
	solve_quadratic(length_squared(v[0]),
		2 * dot(v[0], v[1]), length_squared(v[1]) - pow(cy.r, 2), time);
	dist[0] = dot(cy.nv, vsub(vscale(ray.dir, time[0]), vscale(oc, -1)));
	dist[1] = dot(cy.nv, vsub(vscale(ray.dir, time[1]), vscale(oc, -1)));
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

int	hit_cylinder(t_ray *ray, t_figures elem)
{
	double		time;
	double		y;
	t_cylinder	cy;

	cy = elem.fig.cy;
	time = hit_cylinder_time(*ray, cy, &y);
	if (time < INFINITY && ray->hit.time > time)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point,
					vadd(vscale(cy.nv, y), cy.c)));
		ray->hit.elem = elem;
		return (1);
	}
	return (0);
}

double	hit_cone_time(t_ray ray, t_cone con, double *y)
{
	t_vec3		oc;
	double		cosine;
	double		time[2];
	double		dist[2];

	oc = vsub(ray.o, con.c);
	cosine = cos(con.theta / 2 * M_PI / 180);
	solve_quadratic(pow(dot(ray.dir, con.nv), 2) - pow(cosine, 2),
		2 * (dot(ray.dir, con.nv) * dot(oc, con.nv)
			- dot(ray.dir, oc) * pow(cosine, 2)),
		pow(dot(oc, con.nv), 2) - length_squared(oc) * pow(cosine, 2),
		time);
	dist[0] = dot(con.nv, vsub(vscale(ray.dir, time[0]), vscale(oc, -1)));
	dist[1] = dot(con.nv, vsub(vscale(ray.dir, time[1]), vscale(oc, -1)));
	if (dist[0] >= 0 && dist[0] <= con.height)
	{
		*y = dist[0];
		return (time[0]);
	}
	if (dist[1] >= 0 && dist[1] <= con.height)
	{
		*y = dist[1];
		return (time[1]);
	}
	return (INFINITY);
}

int	hit_cone(t_ray *ray, t_figures elem)
{
	double		time;
	t_vec3		cp;
	t_vec3		oc;
	t_cone		con;
	double		y;

	con = elem.fig.con;
	time = hit_cone_time(*ray, con, &y);
	if (ray->hit.time > time)
	{
		oc = vsub(ray->o, con.c);
		cp = vsub(vscale(ray->dir, time), vscale(oc, -1));
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point,
					vadd(vscale(con.nv, y), con.c)));
		ray->hit.elem = elem;
		return (1);
	}
	return (0);
}
