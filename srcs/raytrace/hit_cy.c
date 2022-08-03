/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/04 02:12:16 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_caps_time(t_ray ray, t_cylinder cy)
{
	double	time[2];
	int		ret[2];
	t_vec3	v[2];
	t_p3	c2;

	c2 = vadd(cy.c, vscale(cy.nv, cy.height));
	time[0] = hit_plane_time(ray.o, ray.dir, cy.c, cy.nv);
	time[1] = hit_plane_time(ray.o, ray.dir, c2, cy.nv);
	v[0] = vadd(ray.o, vscale(ray.dir, time[0]));
	v[1] = vadd(ray.o, vscale(ray.dir, time[1]));
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

int	hit_caps(t_ray *ray, t_figures *elem)
{
	double		time;
	t_cylinder	cy;

	cy = elem->fig.cy;
	time = hit_caps_time(*ray, cy);
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

int	hit_cylinder(t_ray *ray, t_figures *elem)
{
	double		time;
	double		y;
	t_cylinder	cy;
	int			ret;

	cy = elem->fig.cy;
	time = hit_cylinder_time(*ray, cy, &y);
	ret = 0;
	if (time < INFINITY && ray->hit.time > time)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point,
					vadd(vscale(cy.nv, y), cy.c)));
		ray->hit.clr = elem->clr;
		ret = 1;
	}
	ret |= hit_caps(ray, elem);
	return (ret);
}
