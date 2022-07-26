/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:40:09 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/26 19:33:10 by junyopar         ###   ########.fr       */
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

static void	bhaskara(float a, float b, float c, float *res)
{
	float	sqrt_discriminant;
	float	aux[2];

	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
	aux[0] = (-b - sqrt_discriminant) / (2 * a);
	aux[1] = (-b + sqrt_discriminant) / (2 * a);
	if (aux[0] < aux[1])
	{
		res[0] = aux[0];
		res[1] = aux[1];
	}
	else
	{
		res[0] = aux[1];
		res[1] = aux[0];
	}
}
/*end*/

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
