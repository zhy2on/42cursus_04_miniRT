/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:41:33 by junyopar          #+#    #+#             */
/*   Updated: 2022/07/28 18:18:56 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	bhaskara(float a, float b, float c, float *res)
{
	float		sqrt_discriminant;
	float		aux[2];

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

int	hit_sp(t_ray *ray, t_figures *elem)
{
	t_vec3		v_sp2ray;
	float		time[2];

	v_sp2ray = vsub(ray->orig, elem->fig.sp.c);
	bhaskara(length_squared(ray->dir), 2 * dot(ray->dir, v_sp2ray),
		dot(v_sp2ray, v_sp2ray) - pow(elem->fig.sp.r, 2), time);
	if (ray->hit.time > time[0] && time[0] > 0)
	{
		ray->hit.time = time[0];
		ray->hit.point = get_hit_point(*ray);
		ray->hit.nv = normalize(vsub(ray->hit.point, elem->fig.sp.c));
		ray->hit.color = elem->color;
		return (1);
	}
	return (0);
}
