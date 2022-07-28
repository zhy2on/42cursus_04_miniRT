/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:40:09 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/28 17:11:03 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
** hit_utils **
*/

t_vec3	get_hit_point(t_ray ray)
{
	return (vadd(ray.orig, vscale(ray.dir, ray.hit.time)));
}

/*
**  hit_pl
*/
int	hit_pl(t_ray *ray, t_figures *elem)
{
	double	time;
	double	den;

	den = dot(normalize(ray->dir), elem->nv);
	if (!den)
		return (0);
	time = (dot(vsub(elem->fig.pl.p, ray->orig), elem->nv) / den);
	if (ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (dot(ray->dir, elem->nv) > 0)
			elem->nv = vscale(elem->nv, -1);
		ray->hit.nv = elem->nv;
		ray->hit.color = elem->color;
		return (1);
	}
	return (0);
}
