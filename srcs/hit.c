/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:48:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 04:49:04 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

int	hit_plane(t_figures *elem, t_ray *ray)
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

void	get_sphere_root(double root[2], t_ray *ray, t_sphere sp)
{
	double	discriminant;
	t_p3	oc;
	double	k[3];

	oc = vsub(ray->o, sp.c);
	k[0] = dot(ray->dir, ray->dir);
	k[1] = 2 * dot(ray->dir, oc);
	k[2] = dot(oc, oc) - sp.r * sp.r;
	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		root[0] = INFINITY;
		root[1] = INFINITY;
	}
	else
	{
		root[0] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
		root[1] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
	}
}

int	hit_sphere(t_figures *elem, t_ray *ray)
{
	double		time[2];
	t_sphere	sp;

	sp = elem->fig.sp;
	get_sphere_root(time, ray, sp);
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
