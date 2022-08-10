/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 17:14:16 by junyopar         ###   ########.fr       */
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
