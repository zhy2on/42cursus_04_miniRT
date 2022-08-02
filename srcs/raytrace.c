/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:47:08 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/30 20:46:35 by jihoh            ###   ########.fr       */
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
		if (elem->type == PL)
			ret |= hit_plane(ray, elem);
		else if (elem->type == SP)
			ret |= hit_sphere(ray, elem);
		else if (elem->type == CY)
			ret |= hit_cylinder(ray, elem);
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
	int		al_clr;
	int		clr;
	int		vis;
	t_light	*light;

	if (!intersect(rt, ray))
		return (0);
	al_clr = cscale(rt->scene.al_clr, rt->scene.al_br);
	clr = cprod(ray->hit.clr, al_clr);
	light = rt->scene.light;
	while (light)
	{
		vis = !in_shadow(rt, ray->hit, light);
		clr = cadd(clr, vis * ccomp(light, ray->hit));
		light = light->next;
	}
	return (clr);
}
