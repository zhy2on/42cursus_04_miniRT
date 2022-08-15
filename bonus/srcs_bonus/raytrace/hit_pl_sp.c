/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl_sp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 02:10:13 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/15 21:28:21 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_p3	get_hit_point(t_ray ray)
{
	return (vadd(ray.o, vscale(ray.dir, ray.hit.time)));
}

void	solve_quadratic(double a, double b, double c, double root[2])
{
	double	sqrt_disc;
	double	tmp;

	sqrt_disc = sqrt(pow(b, 2) - 4 * a * c);
	root[0] = (-b - sqrt_disc) / (2 * a);
	if (root[0] <= EPSILON)
		root[0] = INFINITY;
	root[1] = (-b + sqrt_disc) / (2 * a);
	if (root[1] <= EPSILON)
		root[1] = INFINITY;
	if (root[1] < root[0])
	{
		tmp = root[1];
		root[1] = root[0];
		root[0] = tmp;
	}
}

double	hit_plane_time(t_ray ray, t_plane pl)
{
	double	denom;
	double	time;

	denom = dot(pl.nv, ray.dir);
	if (denom == 0)
		return (INFINITY);
	time = (dot(pl.nv, vsub(pl.p, ray.o))) / denom;
	if (time <= EPSILON)
		return (INFINITY);
	return (time);
}

int	hit_plane(t_ray *ray, t_figures elem)
{
	double	time;
	t_plane	pl;

	pl = elem.fig.pl;
	time = hit_plane_time(*ray, pl);
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
