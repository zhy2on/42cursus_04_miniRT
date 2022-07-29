/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:47:08 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 04:49:21 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect(t_minirt *rt, t_ray *ray)
{
	int			ret;
	t_figures	*elem;

	ray->hit.time = INFINITY;
	ret = 0;
	elem = rt->scene.figures;
	while (elem)
	{
		if (elem->type == SP)
			ret |= hit_sphere(elem, ray);
		else if (elem->type == PL)
			ret |= hit_plane(elem, ray);
		elem = elem->next;
	}
	return (ret);
}

int	in_shadow(t_minirt *rt, t_hit hit, t_light *light)
{
	t_ray	shadow;

	shadow.o = hit.point;
	shadow.dir = normalize(vsub(light->o, hit.point));
	return (intersect(rt, &shadow));
}

int	raytrace(t_minirt *rt, t_ray *ray)
{
	int		al_color;
	int		color;
	int		vis;
	t_light	*light;

	if (!intersect(rt, ray))
		return (0);
	al_color = cscale(rt->scene.al_clr, rt->scene.al_br);
	color = cprod(ray->hit.clr, al_color);
	light = rt->scene.light;
	while (light)
	{
		vis = !in_shadow(rt, ray->hit, light);
		color = cadd(color, vis * ccomp(light, ray->hit));
		light = light->next;
	}
	return (color);
}
