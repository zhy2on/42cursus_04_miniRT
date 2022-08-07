/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_con.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:14:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/07 21:25:18 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_bottom_time(t_ray ray, t_cone con)
{
	double	time;
	double	r;
	t_p3	c2;
	t_vec3	v;

	c2 = vadd(con.c, vscale(con.nv, con.height));
	time = hit_plane_time(ray.o, ray.dir, c2, con.nv);
	v = vadd(ray.o, vscale(ray.dir, time));
	r = con.height * tan(con.theta / 2 * M_PI / 180);
	if (time < INFINITY && distance(v, c2) <= r)
		return (time);
	return (INFINITY);
}

int	hit_bottom(t_ray *ray, t_figures elem)
{
	double		time;
	t_cone		con;

	con = elem.fig.con;
	time = hit_bottom_time(*ray, con);
	if (ray->hit.time > time)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, con.nv) > 0)
			con.nv = vscale(con.nv, -1);
		ray->hit.nv = con.nv;
		ray->hit.elem = elem;
		return (1);
	}
	return (0);
}

double	hit_cone_time(t_ray ray, t_cone con)
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
		return (time[0]);
	if (dist[1] >= 0 && dist[1] <= con.height)
		return (time[1]);
	return (INFINITY);
}

int	hit_cone(t_ray *ray, t_figures elem)
{
	double		time;
	t_vec3		cp;
	t_vec3		oc;
	t_cone		con;
	int			ret;

	con = elem.fig.con;
	time = hit_cone_time(*ray, con);
	ret = 0;
	if (ray->hit.time > time)
	{
		oc = vsub(ray->o, con.c);
		cp = vsub(vscale(ray->dir, time), vscale(oc, -1));
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(
				vsub(vscale(cp, dot(con.nv, cp) / length_squared(cp)), con.nv));
		ray->hit.elem = elem;
		ret = 1;
	}
	ret |= hit_bottom(ray, elem);
	return (ret);
}
