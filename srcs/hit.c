/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/02 01:16:23 by jihoh            ###   ########.fr       */
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

	den = dot(normalize(ray->dir), elem->nv);
	if (!den)
		return (0);
	time = (dot(vsub(elem->fig.pl.p, ray->o), elem->nv) / den);
	if (ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, elem->nv) > 0)
			elem->nv = vscale(elem->nv, -1);
		ray->hit.nv = elem->nv;
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
		dot(oc, oc) - pow(sp.r, 2), time);
	if (ray->hit.time > time[0] && time[0] > 0)
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, sp.c));
		ray->hit.clr = elem->clr;
		return (1);
	}
	return (0);
}

// double	solve_cylinder(t_ray *ray, t_cylinder cy, double *y, int ret[2])
// {
// 	t_vec3		vu[2];
// 	t_vec3		oc;
// 	t_vec3		co;
// 	double		time[2];
// 	double		dist[2];

// 	oc = vsub(ray->o, cy.c);
// 	vu[0] = vsub(ray->dir, vscale(cy.nv, dot(ray->dir, cy.nv)));
// 	vu[1] = vsub(oc, vscale(cy.nv, dot(oc, cy.nv)));
// 	solve_quadratic(dot(vu[0], vu[0]), 2 * dot(vu[0], vu[1]),
// 		dot(vu[1], vu[1]) - pow(cy.r, 2), time);
// 	co = vsub(cy.c, ray->o);
// 	dist[0] = dot(cy.nv, vsub(vscale(ray->dir, time[0]), co));
// 	dist[1] = dot(cy.nv, vsub(vscale(ray->dir, time[1]), co));
// 	ret[0] = (dist[0] >= 0 && dist[0] <= cy.height && time[0] > EPSILON);
// 	ret[1] = (dist[1] >= 0 && dist[1] <= cy.height && time[1] > EPSILON);
// 	if (ret[0] == 0 & ret[1] == 1)
// 	{
// 		*y = dist[1];
// 		return (time[1]);
// 	}
// 	*y = dist[0];
// 	return (time[0]);
// }

double	calc_cylinder(t_ray *ray, t_cylinder cy, double time[2])
{
	t_vec3		u;
	t_vec3		v;
	t_vec3		oc;
	double		dist[2];

	oc = vsub(ray->o, cy.c);
	u = vsub(ray->dir, vscale(cy.nv, dot(ray->dir, cy.nv)));
	v = vsub(oc, vscale(cy.nv, dot(oc, cy.nv)));
	solve_quadratic(dot(v, v), 2 * dot(v, u), dot(u, u) - pow(cy.r, 2), time);
	dist[0] = dot(cy.nv, vsub(vscale(ray->dir, time[0]), vscale(oc, -1)));
	dist[1] = dot(cy.nv, vsub(vscale(ray->dir, time[1]), vscale(oc, -1)));
	if (!((dist[0] >= 0 && dist[1] <= cy.height && time[0] > EPSILON)
			|| (dist[1] >= 0 && dist[1] <= cy.height && time[0] > EPSILON)))
		return (time[1]);
	return (time[0]);
}

int	hit_cylinder(t_ray *ray, t_figures *elem)
{
	int		ret[2];
	double	time[2];
	double	cy_time;
	double	y;

	cy_time = calc_cylinder(ray, elem->fig.cy, time);
	if ((ret[0] || ret[1]) && ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (ret[0] == false & ret[1] == true)
			ray->hit.normal = v_scale(ray->hit.normal, -1);
		else
			ray->hit.normal = v_norm(v_sub(ray->hit.point,
			v_add(v_scale(elem->normal, y), elem->point)));
		ray->hit.colour = elem->colour;
	}
	return (ret[0] || ret[1]);
}
