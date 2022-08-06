/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl_sp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:10:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 04:16:26 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_plane_time(t_p3 o, t_vec3 dir, t_p3 p, t_vec3 nv)
{
	double	denom;
	double	time;

	denom = dot(nv, dir);
	if (denom == 0)
		return (INFINITY);
	time = (dot(nv, vsub(p, o))) / denom;
	if (time <= EPSILON)
		return (INFINITY);
	return (time);
}

int	hit_plane(t_ray *ray, t_figures elem)
{
	double	time;
	t_plane	pl;

	pl = elem.fig.pl;
	time = hit_plane_time(ray->o, ray->dir, pl.p, pl.nv);
	if (ray->hit.time > time)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, pl.nv) > 0)
			pl.nv = vscale(pl.nv, -1);
		ray->hit.nv = pl.nv;
		ray->hit.elem = elem;
		return (1);
	}
	return (0);
}

int	hit_sphere(t_ray *ray, t_figures elem)
{
	t_vec3		oc;
	t_sphere	sp;
	double		time[2];

	sp = elem.fig.sp;
	oc = vsub(ray->o, sp.c);
	solve_quadratic(length_squared(ray->dir), 2 * dot(ray->dir, oc),
		length_squared(oc) - pow(sp.r, 2), time);
	if (ray->hit.time > time[0])
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, sp.c));
		ray->hit.elem = elem;
		return (1);
	}
	return (0);
}
